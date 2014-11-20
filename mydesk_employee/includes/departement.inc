<?php

/*
 * Page callback for Employee List page
 */
function departement_list(){

  $header = array(
    'dept_id' => array('data' => t('Dept ID'), 'field' => 'd.dept_id'),
    'dept_name' => array('data' => t('Dept. Name'),'field' => 'd.dept_name'),
    'dept_desc' => array('data' => t('Description'),'field' => 'd.dept_desc'),
    'dept_location' => array('data' => t('Location'), 'field' => 'd.dept_location'),
    'dept_phone' => array('data' => t('Phone'), 'field' => 'd.dept_phone'),
    'dept_head' => array('data' => t('Dept. Head'), 'field' => 'd.dept_head'),
  );

  $query = db_select('mydesk_departement','d')
    ->fields('d',array('dept_id','dept_name','dept_desc','dept_location','dept_phone','dept_head'))
    ->extend('PagerDefault')
    ->extend('TableSort')
    ->orderByHeader($header)
    ->limit(15);
  $results = $query->execute();

  $rows = array();
  foreach($results as $row){
    $rows[] = array(
      $row->dept_id,
      $row->dept_name,
      $row->dept_desc,
      $row->dept_location,
      $row->dept_phone,
      $row->dept_head,
    );
  }

  $departement_table = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'empty' => t("No record(s)."),
      'attributes' => array(
        'id' => 'departement-table',
        'class' => array('table')
      ),
      'caption' => '',
      'colgroups' => array(),
      'sticky' => TRUE,
    )
  );

  $menu = "<div class='menu-bar'><a class='btn btn-success' href='".base_path()."mydesk/departement/add'>Add Departement</a></div>";
  //$add_departement_form = drupal_get_form('departement_header_menu');

  // Paging
  $args = array('tags' => array('first','prev','','next','last'));
  $pager = theme('pager',$args);

  //return render($add_employee_form).$employee_table.$pager;
  return $menu.$departement_table.$pager;
}

/*
 * Form add Departement
 */
function departement_add_form($form,&$form_state){
  $form['dept_name'] = array(
    '#type' => 'textfield',
    '#size' => 60,
    '#required' => TRUE,
    '#attributes' => array(
      'placeholder' => array('Departement Name'),
    ),
    '#prefix' => '<div class="row"><div class="col-md-6">'
  );
  $form['dept_desc'] = array(
    '#type' => 'textarea',
    '#rows' => 3,
    '#attributes' => array(
      'placeholder' => array('Description'),
    ),
    '#suffix' => '</div><div class="col-md-6">',
  );
  $form['dept_location'] = array(
    '#type' => 'textfield',
    '#rows' => 255,
    '#attributes' => array(
      'placeholder' => array('Location'),
    ),
  );
  $form['dept_phone'] = array(
    '#type' => 'textfield',
    '#rows' => 15,
    '#attributes' => array(
      'placeholder' => array('Phone/Mobile'),
    ),
  );

  $employee_list = db_query("SELECT employee_id,fullname FROM {mydesk_employee}")->fetchAllKeyed();

  $form['dept_head'] = array(
    '#type' => 'select',
    '#rows' => 255,
    '#attributes' => array(
      'placeholder' => array('Head PIC'),
    ),
    '#options' => $employee_list,
    '#suffix' => '</div></div>'
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
    '#markup' => l(t('Cancel'), 'mydesk/departement'),
  );

  $form['#action'] = url('mydesk/departement/add');

  return $form;

} 

/*
 * Implement hook_submit();
 */
function departement_add_form_submit($form,&$form_state){

  $fields = array(
    'dept_name' => $form_state['values']['dept_name'],
    'dept_desc' => $form_state['values']['dept_desc'],
    'dept_location' => $form_state['values']['dept_location'],
    'dept_phone' => $form_state['values']['dept_phone'],
    'dept_head' => $form_state['values']['dept_head'],

  );

  db_insert('mydesk_departement')
    ->fields($fields)
    ->execute();

  drupal_set_message("Data successfuly added.","info");

  $form_state['redirect'] = '/mydesk/departement';
}

function departement_header_menu($form,&$form_state){
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
