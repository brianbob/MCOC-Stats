<?php

abstract class Stats {

  private $bg;
  private $user;
  private $current_only;
  protected $stats;
  protected $form;

  // Calculates the numbers needed by our stats class.
  abstract protected function queryRecords();

  // Calculates the numbers needed by our stats class.
  abstract protected function calculateStats();

  // Create the chart to represent this data
  abstract protected function createChart();



  function __construct(&$form = array()) {
    // For right now lets set this to false by default. It can be turned on by calling setCurrent()
    $this->current_only = FALSE;
    // For right now lets set this to null by default. It can be changed by calling setUser()
    $this->bg = NULL;
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
   *  Setter for the battlegroup.
   */
  public function setBg($bg) {
    if (isset($bg) && is_numeric($bg)) {
      $this->bg = $bg;
    }

    // @TODO get the bg from the user. THis should be set on their profile.
  }

  /**
   *  Set the stats to only display information for a specific user.
   *
   * @param object $user
   *   The Drupal $user object.
   */
  public function setUser($user) {
    $this->user = $user;

  /**
   * Get all of the individual AQ records.
   * Working on moving this to a class.
   */
  public function getRecords($type, $top_ten = FALSE, $range = 10) {
    // If a cached entry exists, return it
    $cid = 'mcoc_stats:node_types:' . $type;
    if ($cached = cache_get($cid)) {
      return $cached->data;
    }

    // Otherwise query for our data.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $type);

    if($top_ten) {
      $query->fieldOrderBy('field_points', 'value', 'DESC')->range(0, $range);
    }

    if (!is_null($this->user)) {
      $query->fieldCondition('field_member', 'target_id', $this->user);
    }

    if (!is_null($this->bg)) {
      $query->fieldCondition('field_bg_', 'value', $this->bg);
    }

    // Execute the query....
    $records = $query->execute();
    // ...and cache the result.
    cache_set($cid, $records['node'], 'cache', strtotime('+1 day'));

    return $records['node'];
  }

} // End of Class
