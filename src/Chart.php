<?php

abstract class Stats {

  // The drupal form array on which to create the chart.
  protected $form;
  // The array of data used to populate the chart.
  protected $data;
  // The values array that will store our processed data.
  protected $values

  // Abstract function for computing the values needed for the chart to create them.
  abstract protected function computeValues();
  // Function for displaying the chart on the form.
  abstract protected function createChart();

  function __construct($data, &$form = array()) {
    // Save the form so we can add our charts later.
    $this->form = &$form;
    $this->data = $data;
  }

}
