<?php

/**
 * Page callback for the mass upload form.
 */
function mcoc_war_upload_form($form, &$form_state) {
  // Variables!
  $num_bgs = variable_get('mcoc_war_num_bgs', 3);
  $num_members_per_bg = 10;

  // Attach our CSS
  $path = drupal_get_path('module', 'mcoc_stats') . '/css/mcoc_stats.war-upload-form.css';
  $form['#attached']['css'] = array($path);

  // Load up our users and put them into an array.
  $users = entity_load('user');
  $members = array();
  foreach($users as $user) {
    $members[$user->uid] = $user->name;
  }

  $form['date'] = array(
    '#type' => 'date_popup',
    '#timepicker' => 'timepicker',
    '#date_format' => 'm/d/Y',
  );

  $form['opponent'] = array(
    '#type' => 'textfield',
    '#title' => 'Opponent Name',
  );

  $form['our-rating-pre'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Pre-War Rating',
  );

  $form['enemy-rating-post'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Pre-War Rating',
  );

  $form['our-explored'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Explored %',
  );

  $form['enemy-explored'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Explored %',
  );

  $form['our-points'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Points',
  );
  $form['enemy-points'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Points',
  );

  $form['our-rating-change'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Rating Change',
  );

  $form['enemy-rating-change'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Rating Change',
  );

  $form['our-battlegroup-clears'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Battlegroup Clears',
  );

  $form['enemy-battlegroup-clears'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Battlegroup Clears',
  );

  $form['our-attack-bonus'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Attack Bonus',
  );

  $form['enemy-attack-bonus'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Attack Bonus',
  );

  $form['our-defenders-remaining'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Defenders Remaining',
  );

  $form['enemy-defenders-remaining'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Defenders Remaining',
  );

  $form['our-defender-diversity'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Defender Diversity',
  );

  $form['enemy-defender-diversity'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Defender Diversity',
  );

  $form['our-attacker-kills'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Attacker Kills',
  );

  $form['enemy-attacker-kills'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Attacker Kills',
  );

  $form['enemy-defender-kills'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy Defender Kills',
  );

  $form['our-defender-kills'] = array(
    '#type' => 'textfield',
    '#title' => 'Our Defender Kills',
  );

  $form['our-participants'] = array(
    '#type' => 'textfield',
    '#title' => 'Our # of Participants',
  );

  $form['enemy-participants'] = array(
    '#type' => 'textfield',
    '#title' => 'Enemy # of Participants',
  );

  $form['mvp-1'] = array(
    '#type' => 'select',
    '#title' => "MVP #1",
    '#options' => $members,
  );

  $form['mvp-2'] = array(
    '#type' => 'select',
    '#title' => "MVP #2",
    '#options' => $members,
  );

  $form['mvp-3'] = array(
    '#type' => 'select',
    '#title' => "MVP #3",
    '#options' => $members,
  );

  $form['boss'] = array(
    '#type' => 'checkbox',
    '#title' => 'Boss Defeated?',
  );

  $form['victory'] = array(
    '#type' => 'checkbox',
    '#title' => 'Victory?',
  );


  for ($bg=1; $bg <= $num_bgs; $bg++ ) {
    $form["bg-$bg"] = array(
      '#type' => 'fieldset',
      '#title' => t("BG Record #$bg"),
      '#weight' => $bg,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#tree' => TRUE,
      '#container' => TRUE,
    );

    $form["bg-$bg"]['bg_num'] = array(
      '#type' => 'textfield',
      '#title' => 'BG #',
    );
    
    // Formatting help.
    $form["bg-$bg"]['clearall'] = array(
      '#markup' => '<div class="clearall">&nbsp;</div>',
    );

    $form["bg-$bg"]['row_wrapper'] = array(
      '#container' => TRUE,
      '#pre' => '<div class="mass-upload-form-container">',
      '#post' => '</div>',
      '#tree' => TRUE,
    );

    // Create the points form for each member in each bg.
    for ($i=1; $i <= $num_members_per_bg; $i++) {
      // Member select form to be used by our entity reference field.
      $form["bg-$bg"]['row_wrapper'][$i]['member'] = array(
        '#type' => 'select',
        '#title' => "Member $i",
        '#options' => $members,
      );
      
      $form["bg-$bg"]['row_wrapper'][$i]['contribution'] = array(
        '#type' => 'textfield',
        '#title' => "Contribution %",
      );
      
      $form["bg-$bg"]['row_wrapper'][$i]['explored'] = array(
        '#type' => 'textfield',
        '#title' => "Explored %",
        '#default_value' => 0,
      );
      
      $form["bg-$bg"]['row_wrapper'][$i]['defender-kills'] = array(
        '#type' => 'textfield',
        '#title' => "Defender Kills",
      );
      
      $form["bg-$bg"]['row_wrapper'][$i]['attacker-kills'] = array(
        '#type' => 'textfield',
        '#title' => "Attacker Kills",
      );
      
      $form["bg-$bg"]['row_wrapper'][$i]['defender-rating'] = array(
        '#type' => 'textfield',
        '#title' => "Defender Rating",
      );
      // Formatting help.
      $form["bg-$bg"]['row_wrapper'][$i]['clearall'] = array(
        '#markup' => '<div class="clearall">&nbsp;</div>',
      );
    }
  }
  // Ye old save button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit Records',
    '#weight' => $bg,
  );

  return $form;
}

function mcoc_mass_upload_form_submit($form, $form_state) {
  $values = $form_state['values'];
  $num_bgs = variable_get('mcoc_war_num_bgs', 3);

  $bg_entity = array(
    'type' => 'alliance_aq_record',
    'uid' => 1,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );

  $individual_entity = array(
    'type' => 'individual_aq_record',
    'uid' => 1,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );

  // Look at each one of our battlegroups.
  for ($bg=1; $bg <= $num_bgs; $bg++) {
    $nid = mcoc_mass_upload_create_bg_war_record($values, $bg_entity, $bg);
    // Iterate over each member for each bg and create the individual records.
    foreach ($values["bg-$bg"]['row_wrapper'] as $record) {
      mcoc_mass_upload_create_individual_war_record($individual_entity, $record, $nid, $values["bg-$bg"]['date'], $values["bg-$bg"]['bg_num']);
    }
  }
}

/**
 *  Create the BG record for a given AQ.
 */
function mcoc_war_upload_create_bg_war_record($values, $entity, $bg) {
  /*
  // Create the entity and wrap it.
  $bg_entity = entity_create('node', $entity);
  $bg_wrapper = entity_metadata_wrapper('node', $bg_entity);
  // Set some variables.
  $map = $values["bg-$bg"]['map'];
  $day = $values["bg-$bg"]['day'];
  $start_date = $values["bg-$bg"]['date'];
  // The end date is always 24 hours after the start date. We don't track
  // minutes or hours so this should work out nicely.
  $end_date = date('Y-m-d', strtotime($start_date. ' + 1 days'));;
  // Set all of our values on the wrapper
  $bg_wrapper->field_aq_day_num->set($day);
  $bg_wrapper->field_aq_map_num->set($map);
  $bg_wrapper->field_boss_defeated->set($values["bg-$bg"]['boss'][1]);
  $bg_wrapper->field_explored_->set($values["bg-$bg"]['explored']);
  // Identify the battlegroup.
  $bg_wrapper->field_bg_->set($values["bg-$bg"]['bg_num']);
  // Set the start and End date.
  $bg_wrapper->field_date_range->set(array(
    'value' => $start_date,
    'value2' => $end_date,
  ));
  // Set the title to the start date.
  $bg_wrapper->title->set("BG$bg AQ Record (Map $map, Day $day) on $start_date");
  // Save the wrapper.
  $bg_wrapper->save();
  return $bg_entity->nid;
  */
}

/**
  *
  */
function mcoc_mass_upload_create_individual_war_record($entity, $record, $nid, $date, $bg) {
  /*
  // Create the entity and wrap it.
  $ind_entity = entity_create('node', $entity);
  $ind_wrapper = entity_metadata_wrapper('node', $ind_entity);
  $member = $record['member'];
  $comments = isset($record['comments']) ? $record['comments'] : '';
  // Set the values.
  $ind_wrapper->title->set("Individual AQ record for member $member on $date");
  $ind_wrapper->field_aq_record->set($nid);
  $ind_wrapper->field_member->set($member);
  $ind_wrapper->field_points->set($record['points']);
  $ind_wrapper->field_items_used->set($record['items']);
  $ind_wrapper->field_comments->set($comments);
  $ind_wrapper->field_bg_->set($bg);
  // Save the record
  $ind_wrapper->save();
  */
}
