<?php

function mcoc_stats_home(&$form, $form_state) {

  $form['war-bg1'] = array(
    '#markup' =>   l(t('War Stats - BG1'), 'mcoc/stats/war/1', array('attributes' => array('class' => 'square bg war'))),
  );

  $form['war-bg2'] = array(
    '#markup' =>   l(t('War Stats - BG2'), 'mcoc/stats/war/2', array('attributes' => array('class' => 'square bg war'))),
  );

  $form['war-bg3'] = array(
    '#markup' =>   l(t('War Stats - BG3'), 'mcoc/stats/war/3', array('attributes' => array('class' => 'square bg war'))),
  );

  $form['war-alliance'] = array(
    '#markup' =>   l(t('War Stats - Alliance'), 'mcoc/stats/war/0', array('attributes' => array('class' => 'square alliance war'))),
  );

  $form['crystals'] = array(
    '#markup' =>   l(t('Crystal Stats'), 'mcoc/stats/crystals', array('attributes' => array('class' => 'square crystals'))),
  );

  $form['aq-aliance'] = array(
    '#markup' =>   l(t('AQ Stats - Alliance'), 'mcoc/stats/aq/0', array('attributes' => array('class' => 'square alliance aq'))),
  );

  $form['aq-bg1'] = array(
    '#markup' =>   l(t('AQ Stats - BG1'), 'mcoc/stats/aq/1', array('attributes' => array('class' => 'square alliance aq'))),
  );

  $form['aq-bg2'] = array(
    '#markup' =>   l(t('AQ Stats - BG2'), 'mcoc/stats/aq/2', array('attributes' => array('class' => 'square alliance aq'))),
  );

  $form['aq-bg3'] = array(
    '#markup' =>   l(t('AQ Stats - BG3'), 'mcoc/stats/aq/3', array('attributes' => array('class' => 'square alliance aq'))),
  );

  return $form;
}
