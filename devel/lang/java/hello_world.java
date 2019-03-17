class Student {
    private int id;
    private int age;
    public void set_id(int new_id) { id = new_id; }
    public int get_id() { return id; }
    public void set_age(int new_age) { age = new_age; }
    public int get_age() { return age; }
}
class hello_world {
    public static void main(String[] args) {
        System.out.println("Hello World!");
        Student John = new Student();
        John.set_age(18);
        System.out.println("John is " + John.get_age() + " years old.");
        System.out.println("After two years.");
        John.set_age(20);
        System.out.println("John is " + John.get_age() + " years old.");
    }
}
