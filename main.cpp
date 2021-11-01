#include <iostream> // necesara pentru a citi/scrie la iesirea sau intrarea standard

#include <vector>

#include <cmath> // biblioteca necesara pentru functiile ceil si floor

class Cursant {

  protected:
  std::string nume = ""; //std este un namespace(regiune declarativa pentru nume de tipuri, functii, variabile)		
  std::string prenume = ""; //"::" e un operator numit "scope" care precizeaza compilatorului dupa ce nume sa se uite in lista de identificatori
  int varsta = 0; //nu e indicat sa folosim using namespace std pentru ca exista foarte multe elemente definite acolo si e posibil							//sa existe conflicte de nume de indentificator
  double nota = 0;

  public:
    Cursant(const std::string & nume,
      const std::string & prenume, int varsta) 
	  : nume(nume),
	  	prenume(nume),
		varsta(varsta) 
	{}

  virtual std::string toString() {
    return nume + " " + prenume + " " + std::to_string(varsta) + " " + std::to_string(nota) + "\n";
  }

  virtual void primestePunctaj(double punctaj) = 0;

  double getNota() {
    return this -> nota;
  }

};

class Elev: public Cursant {

  public: Elev(const std::string & nume,
    const std::string & prenume, int varsta): Cursant(nume, prenume, varsta) {}
  void primestePunctaj(double punctaj) override {
    nota = std::ceil(punctaj + 1.5);

    if (nota > 10) {
      nota = 10;
    }
  }
  std::string toString() override {
    return "Elev " + nume + " " + prenume + " " + std::to_string(varsta) + " " + std::to_string(nota) + "\n";
  }
};
class Student: public Cursant {

  public: Student(const std::string & nume,
    const std::string & prenume, int varsta): Cursant(nume, prenume, varsta) {}

  void primestePunctaj(double punctaj) override {

    nota = std::floor(punctaj + 0.5);
  }

  std::string toString() override {
    return "Student " + nume + " " + prenume + " " + std::to_string(varsta) + " " + std::to_string(nota) + "\n";
  }
};
class Profesor {

  private:
    std::string materie = "";
  public:
    std::vector < Cursant * > cursanti = std::vector < Cursant * > (300);
  private:
    int count = 0;

  public:
    Profesor(const std::string & materie, std::vector < Cursant * > & cursantia) {

      this -> materie = materie;
      for (int i = 0; i < cursantia.size(); i++) {

        if (count > cursantia.size()) {
          return;
        }

        cursanti[count++] = cursantia[i];
      }
    }
  void evalueaza() {
    for (int i = 0; i < count; i++) {
      cursanti[i] -> primestePunctaj(rand() % 10 + 1);
    }
  }
  virtual void medie() {
    int suma = 0;
    for (int i = 0; i < count; i++) {
      suma += cursanti[i] -> getNota();
      std::cout << cursanti[i] -> getNota() << std::endl;
    }
    std::cout << static_cast < double > (suma) / static_cast < double > (count) << std::endl;
  }
  virtual std::string toString() {
    std::string sir = "Rezultate:\n";
    for (int i = 0; i < count; i++) {
      sir += cursanti[i] -> toString() + " ";
    }
    return sir;
  }
};
class Director {

  /**
   * The Director's constructor should always be private to prevent direct
   * construction calls with the `new` operator.
   */

  protected:
    Director(const std::string value, std::vector < Profesor * > & profesoria): nume(value), profesori(profesoria)  {}

  static Director * director_;

  std::string nume;
  std::vector < Profesor * > profesori = std::vector < Profesor * > (300);
  public:

    /**
     * Singletons should not be cloneable.
     */
    Director(Director & other) = delete;
  /**
   * Singletons should not be assignable.
   */
  void operator = (const Director & ) = delete;
  /**
   * This is the static method that controls the access to the singleton
   * instance. On the first run, it creates a singleton object and places it
   * into the static field. On subsequent runs, it returns the client existing
   * object stored in the static field.
   */

  static Director * GetInstance(const std::string & value,std::vector < Profesor * > &profesoria) {
    /**
     * This is a safer way to create an instance. instance = new Director is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (director_ == nullptr) {
      director_ = new Director(value,profesoria);
    }
    return director_;
  }
  /**
   * Finally, any singleton should define some business logic, which can be
   * executed on its instance.
   */
  void SomeBusinessLogic() {
    std::cout << this -> nume << std::endl;
  }
  void afiseazaPersoaneInstitutie() {
    for (int i = 0; i < profesori.size(); i++) {
        std::cout << profesori[i] -> toString() << std::endl;
      }
  }

  std::string value() const {
    return nume;
  }
};

Director * Director::director_ = nullptr;;

int main(int argc, char ** argv) {
  srand(time(0));
  Student * x = new Student("Nuica", "Roger", 20);
  Elev * y = new Elev("Popa", "Bogdan", 15);
  Elev * z = new Elev("Mircea", "Ion", 55);
  Elev * k = new Elev("Ilie", "Petrica", 17);

  std::vector < Cursant * > cursanti = {
    x,
    y,
    z,
    k
  };
  Profesor * p = new Profesor("Matematica", cursanti);
  p -> evalueaza();
  p -> medie();

  std::vector < Profesor * > profesori = {
    p
  };


  const std::string nume = "Director";
  Director *d = Director::GetInstance(nume, profesori);
  d -> afiseazaPersoaneInstitutie();
  delete p;
  delete z;
  delete y;
  delete x;
  delete k;
  delete d;
}