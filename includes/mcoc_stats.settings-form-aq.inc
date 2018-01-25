<?php

/**
 * Page callback for the mass upload form. 
 */
function mcoc_aq_settings_form($form, &$form_state) {

  $form['mcoc_aq_filter_current'] = array(
      '#type' => 'checkboxes',
      '#title' => 'Limit stats to only current BG members?',
	  '#options' => drupal_map_assoc(array(t('Yes'), t('No'))),
	  '#default_value' => variable_get('mcoc_aq_filter_current'),
  );

  $form['mcoc_aq_num_bgs'] = array(
     '#type' => 'textfield',
    '#title' => 'Number of BGs',
	  '#default_value' => variable_get('mcoc_aq_num_bgs'),
  );

  $form['mcoc_aq_num_top'] = array(
    '#type' => 'textfield',
    '#title' => 'Number of "Top Records" to show',
    '#default_value' => variable_get('mcoc_aq_num_top'),
  );


  return system_settings_form($form);
}