<?php

// @todo Load these settings from a settings page?
DEFINE('NUM_BGS', 1);

/**
 * Page callback for the mass upload form. 
 */
function mcoc_settings_form($form, &$form_state) {
  // Attach our CSS       
  //$path = drupal_get_path('module', 'mcoc_stats') . '/css/mcoc_stats.mass-upload-aq.css';
  //$form['#attached']['css'] = array($path);

  $form['settings'] = array(
    '#markup' => 'No Settings Currently.',
  );

  return $form;
}

function mcoc_mass_upload_form_submit($form, $form_state) {
  
}
