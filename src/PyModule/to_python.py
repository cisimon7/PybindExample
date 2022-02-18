import bindings.exampleModule as Mod
import sys

if __name__ == '__main__':
    print(sys.path)
    print("Hello Script")

    print(Mod.the_answer)

    Mod.say_Hello()

    Mod.MyData(x=3, y=7).print()
    Mod.MyData(y=7).print()

    data89 = Mod.MyData(8, 9)
    print(data89)

    print(data89.__dict__)
