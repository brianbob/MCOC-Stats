<?php

class WarStats extends Stats {

  function __construct(&$form = array()) {
    // Get the module path
    $path = drupal_get_path('module', 'mcoc_stats');
    // Attach our CSS
    $form['#attached']['css'][] = $path . '/css/mcoc_stats.alliance-war.css';
    // Attach our JS
    $form['#attached']['js'][] = $path . '/js/jquery.canvasjs.min.js';
    $form['#attached']['js'][] = $path . '/js/mcoc_stats.alliance-war.js';
    // Call the parent constructor to initialize our variables.
    parent::__construct($form);
  }

  /**
   * The idea here is that this should be called once per object. All the needed stats will be
   * calculated and stored in the stats variable.
   */
  function calculateStats() {
    // Get all of our alliance war records to start with.
    $alliance_records = $this->getRecords('alliance_war_record');
    // Iterate over each of our records.
    foreach ($alliance_records as $alliance_record_id => $alliance_record) {
      // Load the Node for this record.
      $alliance_record_node = node_load($alliance_record_id);
      // Get all the individual records associated with this node.
      $individual_records = $this->getRecords('individual_war_record', $alliance_record_id);
      // Iterate over each of the individual records assoicated with the group record.
      foreach ($individual_records as $individual_record_id => $individual_record) {
        // Load the Node for this record.
        $individual_record_node = node_load($individual_record_id);

        // Caluclate individual stats here
      }
      // Calculate alliance stats here.
      //$this->stats['pot'] = array(x => timestamp, y => value);
    }
  }

  function createPOTChart($individual = FALSE) {

    //foreach ($this->stats['TODO'] as $record) {

    //}
  }

  // Standard 'Missed <event>' table.
  public function createMissedTable() {

  }
}
