<?php

/*
 *  IDEAS:
 *   - Should we pass the form as an object so we can add to it here?
 */

class AQStats {

	private $bg;
	private $query;
	private $current_only;
	private $records;
	private $user;
	private $stats_array;
  private $form;
	// Do we need all these still? These should probably be part of stats_array
	//private $rows;
  //private $user_data;
  //private $points_array;
  //private $rounds_array;
  //private $misses_array;
  //private $users_array;
  //private $aq_array;
  //private $top_ten_array;
  //private $maps_array;
  //private $explored_array;
  //private $individual_points_array;
  //private $top_ten_only;

  /**
   *  Class constructor.
   *
   *  boolean $current
   *    Whether or not to include only current BG membbers.
   *  int $bg
   *    The battlegroup number to generate stats for.
   *  int $user
   *    This should be the uid if loading an individual user, NULL loads all users
   */
	function __construct($current = TRUE, $bg = 2, &$form = array(), $user = FALSE) {
	  $this->current_only = $current;
	  $this->top_ten_only = $top_ten;
	  $this->bg = $bg;
	  $this->stats_array = array();
    $this->form = $form;
    // If type is an integer, then load that user, otherwise NULL to load all users.
    $this->user = is_int($user) ? $user : NULL;
	}


  /**
   *  Get the reoords necessary for our stats.
   *
   *  I think we should update this so that each chart has it's own generate function, and each
   *  one calls this function to get the records it needs. To do this I think we should use a lot
   *  of caching so each chart that needs individual records doesn't repeat the query.
   */
	function queryRecords($type)) {
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

	  if (!is_null($this->$user)) {
	    $query->fieldCondition('field_member', 'target_id', $user);
	  }

	  if (!is_null($this->$bg)) {
	    $query->fieldCondition('field_bg_', 'value', $bg);
	  }

	  $records = $query->execute();
    // Set the records on our object
	  $this->records = $records['node'];
    // And cache it
    cache_set($cid, $records, 'cache', strtotime('+1 day'));
	}


  /**
   *  Iterate over $this->records and fill out $this->stats_array.
   */
	function generateStats() {
    foreach ($this->records as $record) {
      // @TODO calculate stuff here.
    }
	}


  /**
   *  Create a chart. Return a form array for insertion into #markup.
   */
	function createChart($chart) {
    // $this->queryRecords($arguments_here);
    // $this->generateStats($arguments_here);
    // Return form array here.
	}

  function returnForm() {
    return $this->form;
  }

}
