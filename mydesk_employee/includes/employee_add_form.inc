<?php

/*
 * Form add employee
 */
function employee_add($form,&$form_state){
  $form['uid'] = array(
    '#type' => 'textfield',
    '#title' => t('User ID'),
    '#size' => 5,
    '#required' => TRUE,
  );
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#size' => 30,
    '#required' => TRUE,
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#size' => 30,
    '#required' => TRUE,
  );
  $form['fullname'] = array(
    '#type' => 'textfield',
    '#title' => t('Full Name'),
    '#size' => 30,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;

} 

/*
 * Implement hook_submit();
 */
function employee_add_submit($form,&$form_state){

  $fields = array(
    'uid' => $form_state['values']['uid'],
    'username' => $form_state['values']['username'],
    'email' => $form_state['values']['email'],
    'fullname' => $form_state['values']['fullname'],
  );

  db_insert('mydesk_employee')
    ->fields($fields)
    ->execute();

  drupal_set_message("Data successfuly added.","info");

  $form_state['redirect'] = '/mydesk/employee';
}
