<?php

require_once dirname(__FILE__) . '/../src/WarStats.php';

/**
 * Page callback for the AQ stats page.
 */
function mcoc_stats_war ($form, &$form_state) {

  $war_stats = new WarStats($form);
  $war_stats->queryRecords();
  $war_stats->createPOTChart();

  return $form;
}
