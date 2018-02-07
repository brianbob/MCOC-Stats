<?php

abstract class WarStats {

  private $bg;
  private $query;
  private $current_only;
  private $records;
  private $user;
  private $stats_array;
  private $form;

  function __construct(&$form = array()) {
    // For right now lets set this to false by default. It can be turned on by calling setCurrent()
    $this->current_only = FALSE;
    // For right now lets set this to null by default. It can be changed by calling setUser()
    $this->user = NULL;
    // For right now lets set this to null by default. It can be changed by calling setUser()
    $this->bg = NULL;
    // Initialize our stats array
    $this->stats_array = array();
    // Save the form so we can add our charts later.
    $this->form = $form;
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
  function setBg($user) {
    $this->user = $curent;
  }

  /**
   *  Queries for the records needed by our stats class.
   */
  abstract protected function queryRecords($type);

  /**
   *  I think this is too general. This might need to be rolled into a specific chart function.
   */
  function calculateStats() {
    foreach ($this->records as $record) {
      // @TODO calculate stuff here.
    }
  }

  function createPointsOverTimeChart($individual = FALSE) {
    // $this->queryRecords($arguments_here);
    // $this->generateStats($arguments_here);
    // Return form array here.
  }

}
