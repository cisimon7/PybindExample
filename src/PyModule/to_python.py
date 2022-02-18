import bindings.example_module as mod

if __name__ == '__main__':
    print("Hello Script")

    print(mod.the_answer)

    mod.say_Hello()

    mod.MyData(x=3, y=7).print()
    mod.MyData(y=7).print()

    data89 = mod.MyData(8, 9)
    print(data89)

    print(data89.__dict__)
