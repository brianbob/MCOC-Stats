<?php

abstract class TopTenChart extends Chart {

  function __construct(&$form = array()) {
     parent::__construct();
  }


  /**
   * Overrides the Chart class computeValues method.
   */
   function computeValues() {

    foreach($this->data as $data) {
      // Compute the values we need and store them in $this->values
    }

   }

  /**
   * Overrides the Chart class createChart method.
   */
  function createChart(){
    // Pass the $this->values array to the chart.
  }
}
