<?php

// https://stackoverflow.com/a/3443811
require_once 'Stats.php';

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
   *  Queries for the records needed by our stats class.
   */
  function queryRecords($type = 'alliance_war_record') {
    // Setup a cache ID
    $cid = 'mcoc_stats:node_types:' . $type;
    // If a cached entry exists, return it
    if ($cached = cache_get($cid)) {
      return $cached->data;
    }

    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $type);

    // @TODO move this to the charts function. Maybe it should be it's own function?
    //if($this->$top_ten) {
    //  $query->fieldOrderBy('field_points', 'value', 'DESC')->range(0, $range);
    //}

    // @TODO: Add a left join here with the user table so we can add a condition for current
    // members only.

    if (!is_null($this->$user)) {
      $query->fieldCondition('field_member', 'target_id', $user);
    }

    // By default we'll get the data for all BGs, but if specified get only the data for the
    // requested BG.
    if (!is_null($this->$bg)) {
      $query->fieldCondition('field_bg_', 'value', $bg);
    }

    $records = $query->execute();
    // Set the records on our object
    $this->records = $records['node'];
    // And cache it
    cache_set($cid, $records, 'cache', strtotime('+1 day'));
  }

  function createPOTChart($individual = FALSE) {
    ddl($this->records, 'records');
    foreach ($this->records as $record) {

    }
    // $this->queryRecords($arguments_here);
    // $this->generateStats($arguments_here);
  }

  // Standard 'Missed <event>' table.
  public function createMissedTable() {

  }
}
