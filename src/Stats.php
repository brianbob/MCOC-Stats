<?php

abstract class Stats {

  private $bg;
  private $current_only;
  private $user;
  private $range;
  protected $stats;
  protected $form;

  // Calculates the numbers needed by our stats class.
  abstract protected function calculateStats();

  // Standard Points over time chart.
  abstract protected function createPOTChart();

  // Standard 'Missed <event>' table.
  abstract protected function createMissedTable();


  function __construct(&$form = array()) {
    // For right now lets set this to false by default. It can be turned on by calling setCurrent()
    $this->current_only = FALSE;
    // For right now lets set this to null by default. It can be changed by calling setUser()
    $this->user = NULL;
    // For right now lets set this to null by default. It can be changed by calling setUser()
    $this->bg = NULL;
    // For right now lets set this to null by default. It can be changed by calling setUser()
    $this->range = 10;
    // Initialize our stats array
    $this->stats_array = array();
    // Save the form so we can add our charts later.
    $this->form = &$form;
  }

  /**
   *  Set the stats to only display information for current members of each bg.
   */
  public function setCurrent($current = TRUE) {
    $this->current_only = $curent;
  }

  /**
   *  Set the stats to only display information for a specific user.
   */
  public function setUser($bg) {
    $this->bg = $bg;
  }

  /**
   *  Set the stats to only display information for a specific user.
   */
  public function setBg($user) {
    $this->user = $curent;
  }

  /**
   *  Set the stats to only display information for a specific user.
   */
  public function setRange($range) {
    $this->range = $range;
  }

  /**
   * Queries for the records needed by our stats class.
   */
  public function getRecords($node_type, $record_id = NULL) {
    // Setup a cache ID
    if (!is_null($record_id)) {
      $cid = "mcoc_stats:node_types:$node_type:$record_id";
    }
    else {
      $cid = "mcoc_stats:node_types:$node_type";
    }
    // If a cached entry exists, return it
    if ($cached = cache_get($cid)) {
      return $cached->data;
    }
    // If we don't have records cached, query for them.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')->entityCondition('bundle', $node_type);

    // @TODO: Add a left join here with the user table so we can add a condition for current
    // members only.

    if (!is_null($this->user)) {
      $query->fieldCondition('field_member', 'target_id', $this->user);
    }

    if (!is_null($this->bg)) {
      $query->fieldCondition('field_bg_', 'value', $this->bg);
    }

    if (!is_null($record_id)) {
      if ($node_type == 'individual_war_record') {
        $query->fieldCondition("field_war_record", 'target_id', $record_id);
      }
      else {
        $query->fieldCondition("field_aq_record", 'target_id', $record_id);
      }
    }

    $records = $query->execute();

    // And cache it
    cache_set($cid, $records['node'], 'cache', strtotime('+1 day'));
    // ... and return it.
    return $records['node'];
  }
}
