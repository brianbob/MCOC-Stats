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

  $form['enemy-rating-pre'] = array(
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


    $form["bg-$bg"]['boss'] = array(
      '#type' => 'checkbox',
      '#title' => 'Boss Defeated?',
    );

    $form["bg-$bg"]['explored'] = array(
      '#type' => 'textfield',
      '#title' => 'Explored',
    );

    $form["bg-$bg"]['attack-bonus'] = array(
      '#type' => 'textfield',
      '#title' => 'Attack Bonus',
    );

    $form["bg-$bg"]['defenders-remaining'] = array(
      '#type' => 'textfield',
      '#title' => 'Defenders Remaining',
    );

    $form["bg-$bg"]['defender-diversity'] = array(
      '#type' => 'textfield',
      '#title' => 'Defender Diversity',
    );

    $form["bg-$bg"]['attacker-kills'] = array(
      '#type' => 'textfield',
      '#title' => 'Attacker Kills',
    );

    $form["bg-$bg"]['defender-kills'] = array(
      '#type' => 'textfield',
      '#title' => 'Defender Kills`',
    );

    $form["bg-$bg"]['participants'] = array(
      '#type' => 'textfield',
      '#title' => 'Participants',
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

      $form["bg-$bg"]['row_wrapper'][$i]['items'] = array(
        '#type' => 'textfield',
        '#title' => "Items Used",
      );

      $form["bg-$bg"]['row_wrapper'][$i]['comments'] = array(
        '#type' => 'textfield',
        '#title' => "Comments",
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

function mcoc_war_upload_form_submit($form, $form_state) {
  $values = $form_state['values'];
  $num_bgs = variable_get('mcoc_war_num_bgs', 3);
  global $user;

  $individual_entity = array(
    'type' => 'individual_war_record',
    'uid' => $user->uid,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );
  // Create the alliance records
  $ar_id = mcoc_war_upload_create_alliance_war_record($values);
  // Look at each one of our battlegroups.
  for ($bg=1; $bg <= $num_bgs; $bg++) {
    // Iterate over each member for each bg and create the individual records.
    $bg_id = mcoc_mass_upload_create_bg_war_record($values, $ar_id, $bg);
    foreach ($values["bg-$bg"]['row_wrapper'] as $record) {
      mcoc_mass_upload_create_individual_war_record($bg_id, $record, $values);
    }
  }
}

/**
 *  Create the Alliance record for a given war.
 */
function mcoc_war_upload_create_alliance_war_record($values) {
  // Create the entity and wrap it.
  global $user;
  $entity = array(
    'type' => 'alliance_war_record',
    'uid' => $user->uid,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );
  $entity = entity_create('node', $entity);
  $wrapper = entity_metadata_wrapper('node', $entity);
  // Set some variables.
  $opponent = $values['opponent'];
  $start_date = $values['date'];
  // Set all of our values on the wrapper
  $wrapper->title->set("Alliance War Record vs $opponent on $start_date");
  $wrapper->field_victory_->set($values['victory']);
  $wrapper->field_war_rating_pre_->set($values['our-rating-pre']);
  $wrapper->field_points->set($values['our-points']);
  $wrapper->field_rating_change->set($values['our-rating-change']);
  $wrapper->field_enemy_war_rating_pre_->set($values['enemy-rating-pre']);
  $wrapper->field_enemy_points->set($values['enemy-points']);
  $wrapper->field_enemy_rating_change->set($values['enemy-rating-change']);
  $wrapper->field_battlegroup_clears->set($values['our-battlegroup-clears']);
  $wrapper->field_explored_->set($values['our-explored']);
  $wrapper->field_attack_bonus->set($values['our-attack-bonus']);
  $wrapper->field_defender_kills->set($values['our-defender-kills']);
  $wrapper->field_participants->set($values['our-participants']);
  $wrapper->field_mvp_1->set($values['mvp-1']);
  $wrapper->field_mvp_2->set($values['mvp-2']);
  $wrapper->field_mvp_3->set($values['mvp-3']);
  $wrapper->field_enemy_battlegroup_clears->set($values['enemy-battlegroup-clears']);
  $wrapper->field_enemy_explored_->set($values['enemy-explored']);
  $wrapper->field_enemy_attack_bonus->set($values['enemy-attack-bonus']);
  $wrapper->field_enemy_defenders_remaining->set($values['enemy-defenders-remaining']);
  $wrapper->field_defenders_remaining->set($values['our-defenders-remaining']);
  $wrapper->field_enemy_defender_diversity->set($values['enemy-defender-diversity']);
  $wrapper->field_defender_diversity->set($values['our-defender-diversity']);
  $wrapper->field_enemy_attacker_kills->set($values['enemy-attacker-kills']);
  $wrapper->field_attacker_kills->set($values['our-attacker-kills']);
  $wrapper->field_enemy_defender_kills->set($values['enemy-defender-kills']);
  $wrapper->field_enemy_participants->set($values['enemy-participants']);
  // Set the start and End date.
  // The end date is always 48 hours after the start date (1 day for placement, 1 day for attack).
  $end_date = date('Y-m-d', strtotime($start_date. ' + 2 days'));
  $wrapper->field_date_range->set(array(
    'value' => $start_date,
    'value2' => $end_date,
  ));
  // Save the wrapper.
  $wrapper->save();
  return $entity->nid;

}

/**
  *
  */
function mcoc_mass_upload_create_bg_war_record($values, $nid, $bg) {
  // Create the entity and wrap it.
  global $user;
  $entity = array(
    'type' => 'battlegroup_war_record',
    'uid' => $user->uid,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );
  $entity = entity_create('node', $entity);
  $wrapper = entity_metadata_wrapper('node', $entity);
  $opponent = $values['opponent'];
  $start_date = $values['date'];
  // Set the values.
  $wrapper->title->set("Battlegroup War record for BG #$bg vs $opponent on $start_date");
  $wrapper->field_war->set($nid);
  $wrapper->field_bg_->set($bg);
  $wrapper->field_boss_defeated->set($values["bg-$bg"]['boss']);
  $wrapper->field_explored_->set($values["bg-$bg"]['explored']);
  $wrapper->field_attack_bonus->set($values["bg-$bg"]['attack-bonus']);
  $wrapper->field_defenders_remaining->set($values["bg-$bg"]['defenders-remaining']);
  $wrapper->field_defender_diversity->set($values["bg-$bg"]['defender-diversity']);
  $wrapper->field_attacker_kills->set($values["bg-$bg"]['attacker-kills']);
  $wrapper->field_defender_kills->set($values["bg-$bg"]['defender-kills']);
  $wrapper->field_participants->set($values["bg-$bg"]['participants']);
  // Save the record
  $wrapper->save();
}


/**
  *
  */
function mcoc_mass_upload_create_individual_war_record($nid, $record, $values) {
  // Create the entity and wrap it.
  global $user;
  $entity = array(
    'type' => 'individual_war_record',
    'uid' => $user->uid,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );
  $entity = entity_create('node', $entity);
  $wrapper = entity_metadata_wrapper('node', $entity);
  $opponent = $values['opponent'];
  $start_date = $values['date'];

  $member = $record['member'];
  $comments = isset($record['comments']) ? $record['comments'] : '';
  // Set the values.
  $wrapper->title->set("Individual War record for member #$member vs $opponent on $start_date");
  $wrapper->field_battlegroup_instance->set($nid);
  $wrapper->field_member->set($member);
  $wrapper->field_items_used->set($record['items']);
  $wrapper->field_comments->set($comments);
  $wrapper->field_contribution_->set($record['contribution']);
  $wrapper->field_explored_->set($record['explored']);
  $wrapper->field_defender_kills->set($record['defender-kills']);
  $wrapper->field_attacker_kills->set($record['attacker-kills']);
  $wrapper->field_defender_rating->set($record['defender-rating']);
  // Save the record
  $wrapper->save();
}
