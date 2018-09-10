<?php

/*
 *  IDEAS:
 *   - Should we pass the form as an object so we can add to it here?
 */

class AQStats extends Stats {

	private $bg;
	private $query;
	private $current_only;
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
   *  int $user
   *    This should be the uid if loading an individual user, NULL loads all users
   */
	function __construct($current = TRUE, &$form = array(), $user = FALSE) {
    // Do we want to set this as a variable here, or use the setting?
    // $current = variable_get('mcoc_aq_filter_current')['Yes'] === 'Yes';
	  $this->current_only = $current;
	  $this->top_ten_only = $top_ten;
    $this->form = $form;
    // If type is an integer, then load that user, otherwise NULL to load all users.
    $this->user = is_int($user) ? $user : NULL;
	}
}
