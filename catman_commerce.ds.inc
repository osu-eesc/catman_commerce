<?php
/**
 * @file
 * catman_commerce.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function catman_commerce_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'catman_invoice_footer';
  $ds_field->label = 'Catman invoice footer';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'commerce_invoice' => 'commerce_invoice',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'catman_custom|eesc_invoice_footer',
    'block_render' => '1',
  );
  $export['catman_invoice_footer'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'catman_invoice_header';
  $ds_field->label = 'Catman invoice header';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'commerce_invoice' => 'commerce_invoice',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'catman_custom|eesc_invoice_header',
    'block_render' => '1',
  );
  $export['catman_invoice_header'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'catman_order_payment';
  $ds_field->label = 'Catman order payment';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'commerce_invoice' => 'commerce_invoice',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|7d5b7c242f8bc3f4df4c352b3ce257ad',
    'block_render' => '1',
  );
  $export['catman_order_payment'] = $ds_field;

  return $export;
}
