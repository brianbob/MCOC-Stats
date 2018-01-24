<?php
/**
 * @file
 * mcoc_stats.features.inc
 */

/**
 * Implements hook_node_info().
 */
function mcoc_stats_node_info() {
  $items = array(
    'alliance_aq_record' => array(
      'name' => t('Alliance AQ Record'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'alliance_war_record' => array(
      'name' => t('Alliance War Record'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'individual_aq_record' => array(
      'name' => t('Individual AQ Record'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'individual_war_record' => array(
      'name' => t('Individual War Record'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
