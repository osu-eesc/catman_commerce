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
  $items['rules_10_percent_over_100'] = entity_import('rules_config', '{ "rules_10_percent_over_100" : {
      "LABEL" : "10 percent on orders over 100 dollars",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "commerce_price", "rules", "commerce_line_item", "commerce_shipping" ],
      "ON" : { "commerce_shipping_calculate_rate" : [] },
      "IF" : [
        { "commerce_price_compare_price" : {
            "first_price" : [ "commerce-line-item:order:commerce-order-total" ],
            "operator" : "\\u003E",
            "second_price" : { "value" : { "amount" : 10000, "currency_code" : "USD" } }
          }
        },
        { "text_matches" : {
            "text" : [ "commerce-line-item:line-item-label" ],
            "match" : "10% of order total"
          }
        }
      ],
      "DO" : [
        { "data_calc" : {
            "USING" : {
              "input_1" : [ "commerce-line-item:order:commerce-order-total:amount" ],
              "op" : "*",
              "input_2" : "0.1"
            },
            "PROVIDE" : { "result" : { "result" : "Calculation result" } }
          }
        },
        { "commerce_line_item_unit_price_add" : {
            "commerce_line_item" : [ "commerce_line_item" ],
            "amount" : [ "result" ],
            "component_name" : "flat_rate_10_of_total_over_100",
            "round_mode" : "2"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_actual'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_actual" : {
      "LABEL" : "Delete shipping line item then apply shipping (actual)",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
  $items['rules_delete_shipping_line_item_then_apply_shipping_over_100_'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_over_100_" : {
      "LABEL" : "Delete shipping line item then apply shipping (over $100)",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
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
                      "value" : "10000"
                    }
                  }
                ]
              }
            ],
            "DO" : [
              { "commerce_shipping_service_rate_order" : {
                  "shipping_service_name" : "shipping_10_over_100",
                  "commerce_order" : [ "commerce_order" ]
                }
              }
            ],
            "LABEL" : "Add rate for shipping (over $100)"
          }
        }
      ]
    }
  }');
  $items['rules_delete_shipping_line_item_then_apply_shipping_sxty_to_eght'] = entity_import('rules_config', '{ "rules_delete_shipping_line_item_then_apply_shipping_sxty_to_eght" : {
      "LABEL" : "Delete shipping line item then apply shipping ($60.01 to $80)",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
      "OWNER" : "rules",
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
  $items['rules_increment_stock_canceling_order'] = entity_import('rules_config', '{ "rules_increment_stock_canceling_order" : {
      "LABEL" : "Stock: Increase when canceling the order process",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "commerce_ss", "entity" ],
      "ON" : { "commerce_order_update" : [] },
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
      "OWNER" : "rules",
      "TAGS" : [ "catman", "Commerce Checkout" ],
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
      "ON" : { "commerce_product_calculate_sell_price" : [] },
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
  $items['rules_purchase_order_access'] = entity_import('rules_config', '{ "rules_purchase_order_access" : {
      "LABEL" : "Purchase order access",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
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
      "OWNER" : "rules",
      "TAGS" : [ "catman", "Commerce Payment" ],
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
      "ON" : { "commerce_product_calculate_sell_price" : [] },
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
      "OWNER" : "rules",
      "TAGS" : [ "catman", "Commerce Checkout" ],
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_product_reference" ],
      "ON" : { "commerce_product_calculate_sell_price" : [] },
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
  $items['rules_send_ready_for_pickup_email'] = entity_import('rules_config', '{ "rules_send_ready_for_pickup_email" : {
      "LABEL" : "Send ready for pickup email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : { "commerce_order_update" : [] },
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
            "message" : "Thanks again for your [site:name] order. Your order is ready for pickup.\\r\\n\\r\\nYou can pick up your order weekdays between 8:00 a.m. and 5:00 p.m. Pacific Time at our office:\\r\\nExtension and Experiment Station Communications\\r\\nOregon State University\\r\\n422 Kerr Administration Bldg.\\r\\nCorvallis, OR 97331-2119\\r\\n\\r\\nIf you are paying with an OSU index, we will process a journal voucher to complete your order.\\r\\n\\r\\nIf you are paying with a purchase order, payment is due upon receipt of your order. Please forward the invoice (included with your order) to your accounts payable department, and note the payment instructions on the invoice.\\r\\n\\r\\nRemember that you can view the status of your order and your order history with us at any time by logging into your [site:name] account at:\\r\\n[site:login-url]\\r\\n\\r\\nPlease contact us if you have questions. Thank you!\\r\\n\\r\\nExtension and Experiment Station Communications\\r\\nOregon State University\\r\\n422 Kerr Administration Bldg.\\r\\nCorvallis, OR 97331-2119\\r\\nPhone: 541-737-2513 or 800-561-6719\\r\\nEmail: puborders@oregonstate.edu\\r\\nextension.oregonstate.edu\\/catalog",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_shipped_paid_email'] = entity_import('rules_config', '{ "rules_send_shipped_paid_email" : {
      "LABEL" : "Send shipped and paid email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : { "commerce_order_update" : [] },
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
            "message" : "Thanks again for your [site:name] order. Your order has been shipped and is fully paid. This completes your order.\\r\\n\\r\\nRemember that you can view the status of your order and your order history with us at any time by logging into your [site:name] account at: [site:login-url]\\r\\n\\r\\nPlease contact us if you have questions. Thank you!\\r\\n\\r\\nExtension and Experiment Station Communications\\r\\nOregon State University\\r\\n422 Kerr Administration Bldg.\\r\\nCorvallis, OR 97331-2119\\r\\nPhone: 541-737-2513 or 800-561-6719\\r\\nEmail: puborders@oregonstate.edu\\r\\nextension.oregonstate.edu\\/catalog",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_shipped_unpaid_email'] = entity_import('rules_config', '{ "rules_send_shipped_unpaid_email" : {
      "LABEL" : "Send shipped and unpaid email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "catman" ],
      "REQUIRES" : [ "rules", "entity" ],
      "ON" : { "commerce_order_update" : [] },
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
            "message" : "Thanks again for your [site:name] order. Your order has been shipped.\\r\\n\\r\\nIf you are paying with an OSU index, we will process a journal voucher to complete your payment.\\r\\n\\r\\nIf you are paying with a purchase order, payment is due upon receipt of your order. Please forward the invoice (included with your order) to your accounts payable department, and note the payment instructions on the invoice.\\r\\n\\r\\nRemember that you can view the status of your order and your order history with us at any time by logging into your [site:name] account at: [site:login-url]\\r\\n\\r\\nPlease contact us if you have questions. Thank you!\\r\\n\\r\\nExtension and Experiment Station Communications\\r\\nOregon State University\\r\\n422 Kerr Administration Bldg.\\r\\nCorvallis, OR 97331-2119\\r\\nPhone: 541-737-2513 or 800-561-6719\\r\\nEmail: puborders@oregonstate.edu\\r\\nextension.oregonstate.edu\\/catalog",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
