<?php
/**
 * @file
 * catman_commerce.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function catman_commerce_default_rules_configuration() {
  $items = array();
  $items['rules_county_discount_25_off'] = entity_import('rules_config', '{ "rules_county_discount_25_off" : {
      "LABEL" : "County discount 25% off",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Checkout" ],
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
      "ON" : [ "commerce_product_calculate_sell_price" ],
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "6" : "6" } }
          }
        }
      ],
      "DO" : [
        { "commerce_line_item_unit_price_multiply" : {
            "commerce_line_item" : [ "commerce_line_item" ],
            "amount" : ".75",
            "component_name" : "discount",
            "round_mode" : "1"
          }
        }
      ]
    }
  }');
  $items['rules_discount_25_off_message'] = entity_import('rules_config', '{ "rules_discount_25_off_message" : {
      "LABEL" : "Discount 25% off message",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "6" : "6" } }
          }
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Your 25% discount was applied to [commerce_product:title].",
            "repeat" : 0
          }
        }
      ]
    }
  }');
  $items['rules_increment_stock_canceling_order'] = entity_import('rules_config', '{ "rules_increment_stock_canceling_order" : {
      "LABEL" : "Stock: Increase when canceling the order process",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "commerce_ss", "entity" ],
      "ON" : [ "commerce_order_update" ],
      "IF" : [
        { "data_is" : { "data" : [ "commerce-order:status" ], "value" : "canceled" } },
        { "AND" : [
            { "NOT data_is" : { "data" : [ "commerce-order-unchanged:status" ], "value" : "canceled" } }
          ]
        }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "commerce-order:commerce-line-items" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "commerce_ss_increase_by_line_item" : { "commerce_line_item" : [ "list-item" ] } }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_purchase_order_access'] = entity_import('rules_config', '{ "rules_purchase_order_access" : {
      "LABEL" : "Purchase order access",
      "PLUGIN" : "rule",
      "TAGS" : [ "commerce_purchase_order" ],
      "REQUIRES" : [ "rules", "commerce_payment" ],
      "USES VARIABLES" : { "user" : { "label" : "User", "type" : "user" } },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "6" : "6", "5" : "5" } },
            "operation" : "OR"
          }
        },
        { "NOT user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "1" : "1", "2" : "2" } },
            "operation" : "OR"
          }
        }
      ],
      "DO" : [
        { "commerce_payment_enable_commerce_purchase_order" : {
            "commerce_order" : [ "site:current-cart-order" ],
            "payment_method" : { "value" : { "method_id" : "commerce_purchase_order" } }
          }
        }
      ]
    }
  }');
  $items['rules_send_invoice'] = entity_import('rules_config', '{ "rules_send_invoice" : {
      "LABEL" : "Send invoice",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Payment" ],
      "REQUIRES" : [ "rules", "commerce_invoice_receipt", "commerce_payment" ],
      "ON" : [ "commerce_payment_order_paid_in_full" ],
      "DO" : [
        { "commerce_invoice_receipt_action_mail" : {
            "commerce_order" : [ "commerce_order" ],
            "to" : "[commerce-order:owner] \\u003C[commerce-order:mail]\\u003E",
            "subject" : "[site:name]: Order #date([site:current-date], \\u0027Y-m-d\\u0027)-[commerce-order:order-id]"
          }
        }
      ]
    }
  }');
  return $items;
}
