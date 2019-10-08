extern crate json;

use json::{object, array};

fn test_json_basic() {
    let parsed = json::parse(r#"
        {
            "code": 200,
            "success": true,
            "payload": {
                "features": [
                    "awesome",
                    "easyapi",
                    "lowLearningCurve"
                ]
            }
        }
    "#).unwrap();

    let instance = object!{
        "code" => 200,
        "success" => true,
        "payload" => object!{
            "features" => array!{
                "awesome",
                "easyapi",
                "lowLearningCurve"
            }
        }
    };

    assert_eq!(parsed, instance);
} 

pub fn test_json() {

    test_json_basic();
}