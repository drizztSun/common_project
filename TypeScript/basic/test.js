function greets(person) {
    return 'Hello, ' + person.firstName + ' ' + person.lastName;
}
var Student = /** @class */ (function () {
    function Student(firstName, lastName, middleName) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.middleName = middleName;
        this.fullName = firstName + " " + middleName + " " + lastName;
    }
    return Student;
}());
var user = new Student("John", "Smith", "");
document.body.textContent = greets(user);
// error TS2345: Argument of type 'number[]' is not assignable to parameter of type 'string'.
// let user = [0, 1, 2] // array
// document.body.textContent = greets(user)
