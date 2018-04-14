<?php

/**
 * Page callback for the AQ stats page.
 */
function mcoc_stats_aq ($form, &$form_state, $bg_number) {
  // Variables!
  $rows = array();
  $user_data = array();
  $points_array = array();
  $rounds_array = array();
  $misses_array = array();
  $users_array = array();
  $aq_array = array();
  $top_ten_array = array();
  $maps_array = array();
  $explored_array = array();
  $individual_points_array = array();
  $path = drupal_get_path('module', 'mcoc_stats');

  // Attach our CSS
  $form['#attached']['css'][] = $path . '/css/mcoc_stats.alliance-aq.css';
  // Attach our JS
  $form['#attached']['js'][] = $path . '/js/jquery.canvasjs.min.js';
  $form['#attached']['js'][] = $path . '/js/mcoc_stats.alliance-aq.js';
  // Get the bg number from the args.
  $bg = isset($bg_number) ? $bg_number : NULL;
  // Get all our individual aq records.
  $individual_records = mcoc_stats_get_records('individual_aq_record', FALSE, NULL, NULL, $bg);
  //$num_top = variable_get('mcoc_aq_num_top', 10);
  //$top_ten = mcoc_stats_get_records('individual_aq_record', TRUE, $num_top, NULL, $bg);
  // See if we should filter out all non-current members.
  $current = variable_get('mcoc_aq_filter_current')['Yes'] === 'Yes';
  // Iterate over the records.
  foreach ($individual_records as $record) {
    // Load the individual AQ node.
    $individiual_entity = node_load($record->nid);
    // Wrap the individual AQ node.
    $individual_wrapper = entity_metadata_wrapper('node', $individiual_entity);
    // Get the bg Aq node.
    $group_record_id = $individual_wrapper->field_aq_record->value()->nid;
    // Wrap the bg Aq node.
    $group_wrapper = entity_metadata_wrapper('node', $group_record_id);
    // Load the user associated with the record so we can get their name.
    $user = $individual_wrapper->field_member->value();
    // Wrap the user.
    $user_wrapper = entity_metadata_wrapper('user', $user);
    // Save the UID, mostly to save space down below.
    $uid = $user->uid;
    // Check to see first if we're looking for current members only, and if we are if they match.
    if (($current && $user_wrapper->field_bg_->value() == $individual_wrapper->field_bg_->value()) || !$current) {
      $name = "<a href='/user/$uid'>$user->name</a>";
      // Get their points so we can average them.
      $points = (int) $individual_wrapper->field_points->value();
      // Add the username to our list of users.
      $users_array[$user->uid] = $name;
      // Categorize the individual array by date since that's how the chart wants it.
      $date_array = $group_wrapper->field_date_range->value();
      $date_parts = explode( ' ', $date_array['value']);
      $timestamp = strtotime($date_parts[0]) * 1000;
      $individual_points_array[$timestamp][$user->name] = $points;
      //
      $points_array[$uid] = isset($points_array[$uid]) ? $points_array[$uid] += (int) $points : (int) $points;
      // @todo change this to index by date instead of aq record number.
      $aq_array[$group_record_id] = isset($aq_array[$group_record_id]) ? $aq_array[$group_record_id] += (int) $points : (int) $points;
      // Weird... $array_name[$index]++ doesn't seem to work, but $array_name[$index] += 1 does?
      $rounds_array[$uid] = (isset($rounds_array[$uid]) ? $rounds_array[$uid] += 1 : 1);
      // Check to see if his points are zero, meaning this person missed the round.
      if ($points == 0) {
        $misses_array[$uid] = isset($misses_array[$uid]) ? $misses_array[$uid] += 1 : 1;
      }
      else {
        // Add users tothe misses array even if they haven't missed so that we have a full list.
        // @todo initialize this somewhere so we can remove this else.
        $misses_array[$uid] = isset($misses_array[$uid]) ? $misses_array[$uid] : 0;
      }
      //if (array_key_exists($record->nid, $top_ten)) {
      $top_ten_array[$points] = $name;
      //}
      // Record the map number for our stats.
      $map_number = $group_wrapper->field_aq_map_num->value();
      $maps_array[$group_record_id] = $map_number;
      // Record the explored percenage for our dashboards.
      $percent_explored = $group_wrapper->field_explored_->value();
      $explored_array[$group_record_id] = array('map' => $map_number, 'percentage' => $percent_explored);
    }
  }
  // Create "aq points over time" chart.
  mcoc_stats_create_group_points_chart($form, $aq_array);
  // Create the first round of tables.
  mcoc_stats_create_avg_table($form, $users_array, $points_array, $rounds_array);
  // Create the "top ten" table.
  mcoc_stats_create_top_ten_table($form, $top_ten_array);
  // Create the individual points chart
  mcoc_stats_create_individual_points_chart($form, $individual_points_array);
  // Map pie chart
  mcoc_stats_create_map_numbers_chart($form, $maps_array);
  // Create misses table.
  mcoc_stats_create_misses_table($form, $users_array, $misses_array);
  // Create 'explored graph'.
  mcoc_stats_create_explored_graph($form, $explored_array);

  return $form;
}

/**
 * Creates the 'Average points' table.
 */
function mcoc_stats_create_avg_table(&$form, $users, $points, $rounds) {
  // Variables!
  $i = 0;
  $rows = array();
  // Create the header for our table.
  $header = array('#', 'Name', 'Average Points', 'AQs on Record');
  // Calculate our averages
  foreach($points as $id => $score) {
    // Calculate the average points based on the user ID.
    $points[$id] = $score / $rounds[$id];
  }

  // Sort the array by points. This is why our arrays needed to be individual arrays
  // instead of one big array. I had trouble sorting the multi-dimensional arrays :(
  arsort($points);

  foreach($points as $id => $score) {
    $i++;
    // Add the data to our rows array for theme_table()
    $rows[] = array(
      array('data' => $i, 'align' => 'center'),
      array('data' => $users[$id], 'align' => 'center'),
      array('data' => number_format($points[$id], 0), 'align' => 'center'),
      array('data' => $rounds[$id], 'align' => 'center'),
    );
  }
  // Create the form element for our chart to render in and styles to key off of.
  $form['avg'] = array (
    '#prefix' => '<div class="mcoc-table-container left"> <h2>Average Points by Member</h2><div class="mcoc-avg-table mcoc-table">',
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#suffix' =>'</div></div>'
  );
}

/**
 * Creates the 'Misses' table.
 */
function mcoc_stats_create_misses_table(&$form, $users, $misses) {
  // Variables!
  $i = 0;
  $rows = array();

  // Sort the array by points. This is why our arrays needed to be individual arrays
  // instead of one big array. I had trouble sorting the multi-dimensional arrays :(
  arsort($misses);
  // Create the header for our table.
  $header = array('#', 'Name', '# of Missed AQs');
  // Calculate our stats and create the table
  foreach($misses as $id => $miss) {
    $i++;
    // Add the data to our rows array for theme_table()
    $rows[] = array(
      array('data' => $i, 'align' => 'center'),
      array('data' => $users[$id], 'align' => 'center'),
      array('data' => $miss, 'align' => 'center'),
    );
  }
  // Create the form element for our chart to render in and styles to key off of.
  $form['misses'] = array (
    '#prefix' => '<div class="mcoc-table-container" id="misses-table"><h2>Missed AQs by Member</h2><div class="mcoc-misses-table mcoc-table">',
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#suffix' =>'</div></div>'
  );
}

/**
 *
 */
function mcoc_stats_create_group_points_chart(&$form, $aq_array) {
  $overall_values = array();
  $average_values = array();
  $trendline = array();
  $total_thusfar = 0;
  $num_aqs = 0;
  $total_aqs = count($aq_array);

  foreach($aq_array as $aq_id => $aq_points) {
    $node_entity = node_load($aq_id);
    $node_wrapper = entity_metadata_wrapper('node', $node_entity);
    $date_array = $node_wrapper->field_date_range->value();
    $date_parts = explode( ' ', $date_array['value']);
    $timestamp = strtotime($date_parts[0]) * 1000;
    $num_aqs++;
    $total_thusfar += $aq_points;
    // Calculate the individual map values.
    $overall_values[] = array(
      'x' => $timestamp,
      'y' => $aq_points,
    );
    // Calculate the averages over time. This should show progress over time.
    $average_points[] = array(
      'x' => $timestamp,
      'y' => ($total_thusfar / $num_aqs),
    );
    if($num_aqs == 1 || $num_aqs == $total_aqs) {
        $trendline[] = array(
        'x' => $timestamp,
        'y' => ($total_thusfar / $num_aqs),
      );
    }
  }
  // Create our chart
  drupal_add_js(array('mcoc_stats' => array('bg_overall_data' => $overall_values)), array('type' => 'setting'));
  drupal_add_js(array('mcoc_stats' => array('bg_average_data' => $average_points)), array('type' => 'setting'));
  drupal_add_js(array('mcoc_stats' => array('bg_trendline_data' => $trendline)), array('type' => 'setting'));
  // Create the form element for our chart to render in and styles to key off of.
  $form['bg-points-chart'] = array (
    '#prefix' => '<div class="mcoc-chart-container"> <h2>BG2 Total Points Over Time</h2><div class="mcoc-bg-point-chart mcoc-chart">',
    '#markup' => '<div id="bgPointChartContainer">&nbsp;</div>',
    '#suffix' =>'</div></div>'
  );
}

/**
 * Create the individual points chart
 */
function mcoc_stats_create_individual_points_chart(&$form, $individual_points_array) {
  $values = array();

  foreach($individual_points_array as $timestamp => $individuals) {
    foreach($individuals as $name => $points) {
      $values[$name][] = array(
        'x' => $timestamp,
        'y' => (int) $points,
      );
    }
  }

  // Create our chart
  drupal_add_js(array('mcoc_stats' => array('individual_data' => $values)), array('type' => 'setting'));
  // Create the form element for our chart to render in and styles to key off of.
  $form['points-chart'] = array (
    '#prefix' => '<div class="mcoc-chart-container"> <h2>AQ Points by Member</h2> <div class="mcoc-individiual-point-chart mcoc-chart">',
    '#markup' => '<div id="individualPointChartContainer">&nbsp;</div>',
    '#suffix' =>'</div></div>'
  );
}

/**
 * Creates the 'Top Ten points' table.
 *
 * @todo REFACTOR ME
 */
function mcoc_stats_create_top_ten_table(&$form, $top_ten_array) {
  // Variables!
  $i = 0;
  $rows = array();
  $num_top = variable_get('mcoc_aq_num_top', 10);
  // Sort the array by points
  krsort($top_ten_array);
  // Create the header for our table.
  $header = array('#', 'Name', 'Points');
  // Calculate our stats and create the table
  foreach($top_ten_array as $points => $name) {
    if ($i++ >= $num_top) {
      continue;
    }
    // Add the data to our rows array for theme_table()
    $rows[] = array(
      array('data' => $i, 'align' => 'center'),
      array('data' => $name, 'align' => 'center'),
      array('data' => number_format($points, 0), 'align' => 'center'),
    );
  }
  // Create the form element for our chart to render in and styles to key off of.
  $form['top-ten'] = array (
    '#prefix' => '<div class="mcoc-table-container"> <h2>Top Scores All Time</h2><div class="mcoc-top-ten-table mcoc-table">',
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#suffix' =>'</div></div>'
  );
}

/**
 *
 */
function mcoc_stats_create_map_numbers_chart(&$form, $maps_array) {
  $values = array();
  $map_one = 0;
  $map_two = 0;
  $map_three = 0;
  $map_four = 0;
  $map_five = 0;
  $map_six = 0;
  $map_total = 0;

  foreach($maps_array as $map_number) {
    switch ($map_number) {
      case 1:
        $map_one++;
        break;
      case 2:
        $map_two++;
        break;
      case 3:
        $map_three++;
        break;
      case 4:
        $map_four++;
        break;
      case 5:
        $map_five++;
        break;
      case 6:
        $map_six++;
        break;
    }

    $map_total++;
  }

  $values[] = array(
    'label' => 'Map 1',
    'y' => ($map_one / $map_total) * 100,
  );

  $values[] = array(
    'label' => 'Map 2',
    'y' => ($map_two / $map_total) * 100,
  );

  $values[] = array(
    'label' => 'Map 3',
    'y' => ($map_three / $map_total) * 100,
    'exploded' => TRUE
  );

  $values[] = array(
    'label' => 'Map 4',
    'y' => ($map_four / $map_total) * 100,
  );

  $values[] = array(
    'label' => 'Map 5',
    'y' => ($map_five / $map_total) * 100,
  );

  $values[] = array(
    'label' => 'Map 6',
    'y' => ($map_six / $map_total) * 100,
  );

  // Create our chart
  drupal_add_js(array('mcoc_stats' => array('map_number_data' => $values)), array('type' => 'setting'));
  // Create the form element for our chart to render in and styles to key off of.
  $form['map-number-chart'] = array (
    '#prefix' => '<div class="mcoc-chart-container" id="map-number-pie-chart"> <h2>Map Selection</h2> <div class="mcoc-map-number-chart mcoc-chart">',
    '#markup' => '<div id="mapNumberChartContainer">&nbsp;</div>',
    '#suffix' =>'</div></div>'
  );
}

/**
 *
 */
function mcoc_stats_create_explored_graph(&$form, $maps_array) {
  $values = array();
  $map_one_explored = 0;
  $map_one_num = 0;
  $map_two_explored = 0;
  $map_two_num = 0;
  $map_three_explored = 0;
  $map_three_num = 0;
  $map_four_explored = 0;
  $map_four_num = 0;
  $map_five_explored = 0;
  $map_five_num = 0;
  $map_six_explored = 0;
  $map_six_num = 0;

  foreach($maps_array as $map) {
    switch ($map['map']) {
      case 1:
        $map_one_explored += $map['percentage'];
        $map_one_num++;
        break;
      case 2:
        $map_two_explored += $map['percentage'];
        $map_two_num++;
        break;
      case 3:
        $map_three_explored += $map['percentage'];
        $map_three_num++;
        break;
      case 4:
        $map_four_explored += $map['percentage'];
        $map_four_num++;
        break;
      case 5:
        $map_five_explored += $map['percentage'];
        $map_five_num++;
        break;
      case 6:
        $map_six_explored += $map['percentage'];
        $map_six_num++;
        break;
    }
  }
  $map_one_explored = empty($map_one_explored) ? 0 : $map_one_explored / $map_one_num;
  $map_two_explored = empty($map_two_explored) ? 0 : $map_two_explored / $map_two_num;
  $map_three_explored = empty($map_three_explored) ? 0 : $map_three_explored / $map_three_num;
  $map_four_explored = empty($map_four_explored) ? 0 : $map_four_explored / $map_four_num;
  $map_five_explored = empty($map_five_explored) ? 0 : $map_five_explored / $map_five_num;
  $map_six_explored = empty($map_six_explored) ? 0 : $map_six_explored / $map_six_num;

  $values[] = array(
    'y' => $map_one_explored,
    'label' => 'Map 1',
  );

  $values[] = array(
    'y' => $map_two_explored,
    'label' => 'Map 2',
  );

  $values[] = array(
    'y' => $map_three_explored,
    'label' => 'Map 3',
  );

  $values[] = array(
    'y' => $map_four_explored,
    'label' => 'Map 4',
  );

  $values[] = array(
    'y' => $map_five_explored,
    'label' => 'Map 5',
  );

  $values[] = array(
    'y' => $map_six_explored,
    'label' => 'Map 6',
  );
  // Create our chart
  drupal_add_js(array('mcoc_stats' => array('explored_data' => $values)), array('type' => 'setting'));
  // Create the form element for our chart to render in and styles to key off of.
  $form['explored-chart'] = array (
    '#prefix' => '<div class="mcoc-chart-container" id="explored-bar-chart"> <h2>Average Exploration % by Map</h2> <div class="mcoc-chart">',
    '#markup' => '<div id="exploredChartContainer">&nbsp;</div>',
    '#suffix' =>'</div></div>'
  );
}
