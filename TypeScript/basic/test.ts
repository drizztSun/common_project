
interface Person {
    firstName: string;
    lastName: string;
}


function greets( person: Person) {
    return 'Hello, ' + person.firstName + ' ' + person.lastName;
}

class Student {
    fullName: string

    public constructor(public firstName: string, public lastName: string, public middleName: string) {
        this.fullName = firstName +  " " + middleName + " " + lastName;
    }
}



let user = new Student("John", "Smith", "");

document.body.textContent = greets(user)

// error TS2345: Argument of type 'number[]' is not assignable to parameter of type 'string'.
// let user = [0, 1, 2] // array
// document.body.textContent = greets(user)