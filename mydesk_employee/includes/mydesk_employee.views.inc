<?php

/*
 * Implement hook_views_data
 */
function mydesk_employee_views_data(){
  $data = array();
  $data['mydesk_employee']['table']['group'] = t('myDesk Employee');
  $data['mydesk_employee']['table']['base'] = array(
    'field' => 'employee_id',
    'title' => t('myDesk Employee'),
    'help' => t('Contain employee data'),
  );
  $data['mydesk_employee']['table']['join'] = array(
    'node' => array(
      'left_field' => 'employee_id',
      'field' => 'employee_id',
    ),
  );

  $data['mydesk_employee']['employee_id'] = array(
    'title' => t('Employee ID'),
    'help' => t('The ID for employee data'),
    'relationship' => array(
      'base' => 'node', // The name of the table to join with.
      'base field' => 'employee_id', // The name of the field on the joined table.
      // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
      'handler' => 'views_handler_relationship',
      'label' => t('Employee ID label'),
      'title' => t('Employee ID title'),
      'help' => t('More information on this relationship'),
    ),
  );

  $data['mydesk_employee']['fullname'] = array(
    'title' => t('Employee Full Name'),
    'help' => t('Employee\'s Full Name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),  
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mydesk_employee']['city'] = array(
    'title' => t('Employee city'),
    'help' => t('City of employee living'),
    'field' => array(
      'handler' => 'views_handler_field'
    ),
    'sort' => array(
      'handler' => 'views_handler_sort'
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string'
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mydesk_employee']['province'] = array(
    'title' => t('Employee Province'),
    'help' => t('Employee\'s Province'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),  
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mydesk_employee']['country'] = array(
    'title' => t('Employee Country'),
    'help' => t('Employee\'s Country'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),  
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mydesk_employee']['postcode'] = array(
    'title' => t('Employee Postcode'),
    'help' => t('Employee\'s Postcode'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),  
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mydesk_employee']['email'] = array(
    'title' => t('Employee Email'),
    'help' => t('Employee\'s Email'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),  
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mydesk_employee']['phone'] = array(
    'title' => t('Employee Phone'),
    'help' => t('Employee\'s Phone'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),  
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;

}
