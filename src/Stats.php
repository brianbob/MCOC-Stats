<?php

abstract class Stats {

  private $bg;
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



}
