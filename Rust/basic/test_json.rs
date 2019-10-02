extern crate json;


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

    let instance = json::object!{
        "code" => 200,
        "success" => true,
        "payload" => json::object!{
            "features" => json::array!{
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