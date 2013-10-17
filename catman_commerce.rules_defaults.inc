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
  $items['rules_delete_shipping_line_item_then_apply_shipping_actual'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_actual" : {
      "LABEL" : "Delete shipping line item then apply shipping (actual)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "user_has_role" : {
                  "account" : [ "site:current-user" ],
                  "roles" : { "value" : { "9" : "9" } }
                }
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "actual_shipping",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping (actual)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_eght_to_hun'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_eght_to_hun" : {
      "LABEL" : "Delete shipping line item then apply shipping ($80.01 to $100)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "NOT user_has_role" : {
                      "account" : [ "site:current-user" ],
                      "roles" : { "value" : { "6" : "6", "9" : "9" } },
                      "operation" : "OR"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003E",
                      "value" : "8000"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003C",
                      "value" : "10001"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "eighty_to_hundred",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping ($80.01 to $100)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_five_or_less'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_five_or_less" : {
      "LABEL" : "Delete shipping line item then apply shipping ($5 or less)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "NOT user_has_role" : {
                      "account" : [ "site:current-user" ],
                      "roles" : { "value" : { "6" : "6", "9" : "9" } },
                      "operation" : "OR"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003C",
                      "value" : "501"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "five_or_less",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping ($5 or less)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_five_to_ten'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_five_to_ten" : {
      "LABEL" : "Delete shipping line item then apply shipping ($5.01 to $10)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "NOT user_has_role" : {
                      "account" : [ "site:current-user" ],
                      "roles" : { "value" : { "6" : "6", "9" : "9" } },
                      "operation" : "OR"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003E",
                      "value" : "500"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003C",
                      "value" : "1001"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "five_to_ten",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping ($5.01 to $10)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_free'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_free" : {
      "LABEL" : "Delete shipping line item then apply shipping (free)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "user_has_role" : {
                  "account" : [ "site:current-user" ],
                  "roles" : { "value" : { "6" : "6" } }
                }
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "free",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping (free)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_free_campus'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_free_campus" : {
      "LABEL" : "Delete shipping line item then apply shipping (free campus mail)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "user_has_role" : {
                  "account" : [ "site:current-user" ],
                  "roles" : { "value" : { "6" : "6" } }
                }
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "free_campus_mail",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping (free campus mail)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_free_shuttle'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_free_shuttle" : {
      "LABEL" : "Delete shipping line item then apply shipping (free state shuttle)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "user_has_role" : {
                  "account" : [ "site:current-user" ],
                  "roles" : { "value" : { "6" : "6" } }
                }
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "free_state_shuttle",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping (free state shuttle)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_frty_to_sxty'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_frty_to_sxty" : {
      "LABEL" : "Delete shipping line item then apply shipping ($40.01 to $60)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "NOT user_has_role" : {
                      "account" : [ "site:current-user" ],
                      "roles" : { "value" : { "6" : "6", "9" : "9" } },
                      "operation" : "OR"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003E",
                      "value" : "4000"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003C",
                      "value" : "6001"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "forty_to_sixty",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping ($40.01 to $60)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_sxty_to_eght'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_sxty_to_eght" : {
      "LABEL" : "Delete shipping line item then apply shipping ($60.01 to $80)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "NOT user_has_role" : {
                      "account" : [ "site:current-user" ],
                      "roles" : { "value" : { "6" : "6", "9" : "9" } },
                      "operation" : "OR"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003E",
                      "value" : "6000"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003C",
                      "value" : "8001"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "sixty_to_eighty",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping ($60.01 to $80)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_ten_to_twent'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_ten_to_twent" : {
      "LABEL" : "Delete shipping line item then apply shipping ($10.01 to $20)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "NOT user_has_role" : {
                      "account" : [ "site:current-user" ],
                      "roles" : { "value" : { "6" : "6", "9" : "9" } },
                      "operation" : "OR"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003E",
                      "value" : "1000"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003C",
                      "value" : "2001"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "ten_to_twenty",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping ($10.01 to $20)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_twty_to_frty'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_twty_to_frty" : {
      "LABEL" : "Delete shipping line item then apply shipping ($20.01 to $40)",
      "PLUGIN" : "rule set",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_shipping", "rules" ],
      "USES VARIABLES" : { "commerce_order" : { "label" : "Commerce Order", "type" : "commerce_order" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "commerce_shipping_delete_shipping_line_items" : { "commerce_order" : [ "commerce_order" ] } }
            ],
            "LABEL" : "Delete shipping line item"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "NOT user_has_role" : {
                      "account" : [ "site:current-user" ],
                      "roles" : { "value" : { "6" : "6", "9" : "9" } },
                      "operation" : "OR"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003E",
                      "value" : "2000"
                    }
                  },
                  { "data_is" : {
                      "data" : [ "commerce-order:commerce-order-total:amount" ],
                      "op" : "\\u003C",
                      "value" : "4001"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "twenty_to_forty",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping ($20.01 to $40)"
          }
        }
      ]
    }
  }');
  $items['rules_discount_25_off_message'] = entity_import('rules_config', '{ "rules_discount_25_off_message" : {
      "LABEL" : "Discount 25% off message",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "6" : "6", "5" : "5" } },
            "operation" : "OR"
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
  $items['rules_osu_affiliate_discount_25_off'] = entity_import('rules_config', '{ "rules_osu_affiliate_discount_25_off" : {
      "LABEL" : "OSU affiliate discount 25% off",
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
  $items['rules_osu_index'] = entity_import('rules_config', '{ "rules_osu_index" : {
      "LABEL" : "OSU index",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-1",
      "ACTIVE" : false,
      "TAGS" : [ "Commerce Payment" ],
      "REQUIRES" : [ "rules", "commerce_payment" ],
      "ON" : [ "commerce_payment_methods" ],
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "6" : "6" } },
            "operation" : "OR"
          }
        },
        { "NOT user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "5" : "5", "9" : "9", "8" : "8" } },
            "operation" : "OR"
          }
        }
      ],
      "DO" : [
        { "commerce_payment_enable_commerce_purchase_order" : {
            "commerce_order" : [ "commerce-order" ],
            "payment_method" : { "value" : {
                "method_id" : "commerce_purchase_order",
                "settings" : {
                  "commerce_purchase_order_length" : "0",
                  "commerce_purchase_order_instructions" : "Please enter your OSU index and activity code. "
                }
              }
            }
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
            "roles" : { "value" : { "1" : "1", "2" : "2", "8" : "8" } },
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
  $items['rules_quanity_discount_100'] = entity_import('rules_config', '{ "rules_quanity_discount_100" : {
      "LABEL" : "Quantity discount 25%",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Payment" ],
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
      "ON" : [ "commerce_product_calculate_sell_price" ],
      "IF" : [
        { "data_is" : {
            "data" : [ "commerce-line-item:quantity" ],
            "op" : "\\u003E",
            "value" : "99"
          }
        },
        { "NOT user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "6" : "6", "5" : "5", "9" : "9" } },
            "operation" : "OR"
          }
        }
      ],
      "DO" : [
        { "commerce_line_item_unit_price_multiply" : {
            "commerce_line_item" : [ "commerce_line_item" ],
            "amount" : ".75",
            "component_name" : "base_price",
            "round_mode" : "1"
          }
        }
      ]
    }
  }');
  $items['rules_reseller_discount_25_off'] = entity_import('rules_config', '{ "rules_reseller_discount_25_off" : {
      "LABEL" : "Reseller discount 25% off",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Checkout" ],
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
      "ON" : [ "commerce_product_calculate_sell_price" ],
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "5" : "5" } }
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
  $items['rules_send_invoice'] = entity_import('rules_config', '{ "rules_send_invoice" : {
      "LABEL" : "Send invoice after completed order",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce Payment" ],
      "REQUIRES" : [ "rules", "commerce_catman_invoice", "commerce_checkout" ],
      "ON" : [ "commerce_checkout_complete" ],
      "DO" : [
        { "commerce_catman_invoice_action_mail" : {
            "commerce_order" : [ "commerce_order" ],
            "to" : "[commerce-order:owner] \\u003C[commerce-order:mail]\\u003E",
            "subject" : "[site:name]: Order #date([site:current-date], \\u0027Y-m-d\\u0027)-[commerce-order:order-id]"
          }
        }
      ]
    }
  }');
  $items['rules_send_order_confirmation_email_eesc'] = entity_import('rules_config', '{ "rules_send_order_confirmation_email_eesc" : {
      "LABEL" : "Send order confirmation email to EESC",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "rules", "commerce_checkout" ],
      "ON" : [ "commerce_checkout_complete" ],
      "DO" : [
        { "mail" : {
            "to" : "bryan.mayjor@oregonstate.edu, jennifer.alexander@oregonstate.edu",
            "subject" : "OSU Extension Catalog order received (order [commerce-order:order-number])",
            "message" : "A new [site:name] order has been received. Log into CatMan to review and process this order.\\r\\n\\r\\nOrder number: [commerce-order:order-number]\\r\\n[commerce-order:admin-url]\\r\\n\\r\\n\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_ready_for_pickup_email'] = entity_import('rules_config', '{ "rules_send_ready_for_pickup_email" : {
      "LABEL" : "Send ready for pickup email",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : [ "commerce_order_update" ],
      "IF" : [
        { "AND" : [
            { "data_is" : { "data" : [ "commerce-order:status" ], "value" : "ready_for_pickup" } },
            { "NOT data_is" : {
                "data" : [ "commerce-order:status" ],
                "value" : [ "commerce-order-unchanged:status" ]
              }
            }
          ]
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[commerce-order:mail]",
            "subject" : "Your [site:name] order is ready for pickup (order [commerce-order:order-number])",
            "message" : "Thanks again for your [site:name] order. Your order is ready for pickup.\\r\\n\\r\\nYou can pick up your order at LOCATION HOURS, ETC. What should we put here?\\r\\n\\r\\nIf you paid with a credit card, order will be complete....something, something.\\r\\n\\r\\nIf you are paying with a purchase order, payment is due upon receipt. Please forward the invoice (included with your order) to your accounts payable department, and note the payment instructions on the invoice.\\r\\n\\r\\nIf you are paying with an OSU index, we will process a journal voucher to complete your order.\\r\\n\\r\\nRemember that you can view the status of your order and your order history with us at any time by logging into your [site:name] account at:\\r\\n[site:login-url]\\r\\n\\r\\nPlease contact us if you have questions. Thank you!\\r\\n\\r\\nExtension and Experiment Station Communications\\r\\nOregon State University\\r\\n422 Kerr Administration Bldg.\\r\\nCorvallis, OR 97331-2119\\r\\nPhone: 541-737-2513 or 800-561-6719\\r\\nEmail: puborders@oregonstate.edu\\r\\nextension.oregonstate.edu\\/catalog",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_shipped_paid_email'] = entity_import('rules_config', '{ "rules_send_shipped_paid_email" : {
      "LABEL" : "Send shipped and paid email",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : [ "commerce_order_update" ],
      "IF" : [
        { "AND" : [
            { "data_is" : { "data" : [ "commerce-order:status" ], "value" : "shipped_paid" } },
            { "NOT data_is" : {
                "data" : [ "commerce-order:status" ],
                "value" : [ "commerce-order-unchanged:status" ]
              }
            }
          ]
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[commerce-order:mail]",
            "subject" : "Your [site:name] order has shipped (order [commerce-order:order-number])",
            "message" : "Thanks again for your [site:name] order. Your order has been shipped. Because you\\u0027ve already paid with a credit card, this completes your order.\\r\\n\\r\\nRemember that you can view the status of your order and your order history with us at any time by logging into your [site:name] account at:\\r\\n[site:login-url]\\r\\n\\r\\nPlease contact us if you have questions. Thank you!\\r\\n\\r\\nExtension and Experiment Station Communications\\r\\nOregon State University\\r\\n422 Kerr Administration Bldg.\\r\\nCorvallis, OR 97331-2119\\r\\nPhone: 541-737-2513 or 800-561-6719\\r\\nEmail: puborders@oregonstate.edu\\r\\nextension.oregonstate.edu\\/catalog",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_shipped_unpaid_email'] = entity_import('rules_config', '{ "rules_send_shipped_unpaid_email" : {
      "LABEL" : "Send shipped and unpaid email",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : [ "commerce_order_update" ],
      "IF" : [
        { "AND" : [
            { "data_is" : { "data" : [ "commerce-order:status" ], "value" : "shipped_unpaid" } },
            { "NOT data_is" : {
                "data" : [ "commerce-order:status" ],
                "value" : [ "commerce-order-unchanged:status" ]
              }
            }
          ]
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[commerce-order:mail]",
            "subject" : "Your [site:name] order has shipped (order [commerce-order:order-number])",
            "message" : "Thanks again for your [site:name] order. Your order has been shipped.\\r\\n\\r\\nIf you are paying with a purchase order, payment is due upon receipt. Please forward the invoice (included with your order) to your accounts payable department, and note the payment instructions on the invoice.\\r\\n\\r\\nIf you are paying with an OSU index, we will process a journal voucher to complete your order.\\r\\n\\r\\nRemember that you can view the status of your order and your order history with us at any time by logging into your [site:name] account at:\\r\\n[site:login-url]\\r\\n\\r\\nPlease contact us if you have questions. Thank you!\\r\\n\\r\\nExtension and Experiment Station Communications\\r\\nOregon State University\\r\\n422 Kerr Administration Bldg.\\r\\nCorvallis, OR 97331-2119\\r\\nPhone: 541-737-2513 or 800-561-6719\\r\\nEmail: puborders@oregonstate.edu\\r\\nextension.oregonstate.edu\\/catalog",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
