<?php

/*
 * Page callback for Employee List page
 */
function employee_list(){

  $header = array(
    'employee_id' => array('data' => t('Staff ID'), 'field' => 's.employee_id'),
    'fullname' => array('data' => t('Fullname'),'field' => 's.fullname'),
    'city' => array('data' => t('City'),'field' => 's.city'),
    'province' => array('data' => t('Province'), 'field' => 's.province'),
    'country' => array('data' => t('Country'), 'field' => 's.country'),
    'postcode' => array('data' => t('Postcode'), 'field' => 's.postcode'),
    'email' => array('data' => t('Email'), 'field' => 's.email'),
    'phone' => array('data' => t('Phone'), 'field' => 's.phone')
  );

  $query = db_select('mydesk_employee','s')
    ->fields('s',array('employee_id','fullname','city','province','country','postcode','email','phone'))
    ->extend('PagerDefault')
    ->extend('TableSort')
    ->orderByHeader($header)
    ->limit(15);
  $results = $query->execute();

  $rows = array();
  foreach($results as $row){
    $rows[] = array(
      $row->employee_id,
      $row->fullname,
      $row->city,
      $row->province,
      $row->country,
      $row->postcode,
      $row->email,
      $row->phone,
    );
  }

  $employee_table = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'empty' => t("No record(s)."),
      'attributes' => array(
        'id' => 'employee-table',
        'class' => array('table')
      ),
      'caption' => '',
      'colgroups' => array(),
      'sticky' => TRUE,
    )
  );

  $menu = "<div class='menu-bar'><a class='btn btn-success' href='".base_path()."mydesk/employee/add'>Add Employee</a></div>";
  $add_employee_form = drupal_get_form('employee_header_menu');

  // Paging
  $args = array('tags' => array('first','prev','','next','last'));
  $pager = theme('pager',$args);

  //return render($add_employee_form).$employee_table.$pager;
  return $menu.$employee_table.$pager;
}

function employee_header_menu($form,&$form_state){
  $form['markup'] = array(
    '#type' => 'button',
    '#value' => 'Add Staff',
    '#ajax' => array(
      'callback' => 'show_add_employee',
      'wrapper' => 'add_employee_wrapper',
      'method' => 'html',
      'effect' => 'fade',
    ),
  );

  $form['add_employee_wrapper'] = array(
    '#type' => 'markup',
    '#markup' => '<div id="add_employee_wrapper"></div>', 
  );

  return $form;
}

function show_add_employee(){
  return drupal_get_form('employee_add');
}


/*
 * Form add employee
 */
function employee_add($form,&$form_state){
  $form['fullname'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#required' => TRUE,
    '#prefix' => '<div class="row"><div class="col-md-6">',
    '#attributes' => array(
      'placeholder' => array('Full Name'),
    ),
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#required' => TRUE,
    '#attributes' => array(
      'placeholder' => array('Email Address'),
    ),
  );
  $form['city'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#required' => FALSE,
    '#attributes' => array(
      'placeholder' => array('City'),
    ),
  );
  $form['province'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#required' => FALSE,
    '#suffix' => '</div><div class="col-md-6">',
    '#attributes' => array(
      'placeholder' => array('Province'),
    ),
  );
  $form['country'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#required' => FALSE,
    '#attributes' => array(
      'placeholder' => array('Country'),
    ),
  );
  $form['postcode'] = array(
    '#type' => 'textfield',
    '#size' => 6,
    '#maxlength' => 6,
    '#attributes' => array(
      'placeholder' => array('Postcode'),
    ),
  );
  $form['phone'] = array(
    '#type' => 'textfield',
    '#size' => 15,
    '#maxlength' => 15,
    '#suffix' => '</div></div>',
    '#attributes' => array(
      'placeholder' => array('Phone/Mobile'),
    ),
  );
  $form['created'] = array(
    '#type' => 'hidden',
    '#default_value' => time(),
  );
  $form['action']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['action']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'mydesk/employee'),
  );

  $form['#action'] = url('mydesk/employee/add');

  return $form;

} 

/*
 * Implement hook_submit();
 */
function employee_add_submit($form,&$form_state){

  $fields = array(
    'email' => $form_state['values']['email'],
    'fullname' => $form_state['values']['fullname'],
    'city' => $form_state['values']['city'],
    'province' => $form_state['values']['province'],
    'country' => $form_state['values']['country'],
    'postcode' => $form_state['values']['postcode'],
    'phone' => $form_state['values']['phone'],
    'created' => $form_state['values']['created'],

  );

  db_insert('mydesk_employee')
    ->fields($fields)
    ->execute();

  drupal_set_message("Data successfuly added.","info");

  $form_state['redirect'] = '/mydesk/employee';
}
