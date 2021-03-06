## Overview

![Prezentacja AiSD (0)](https://user-images.githubusercontent.com/49908210/167669112-412343c7-bbaa-405a-b70f-1ebcdd3aca3f.svg)
![Prezentacja AiSD (1)](https://user-images.githubusercontent.com/49908210/167669468-eed2fbaf-97dd-44ff-94e0-577c2d163e87.svg)
![Prezentacja AiSD (2)](https://user-images.githubusercontent.com/49908210/167669474-d54b490f-ef9c-46a2-b8da-33817985b04a.svg)
![Prezentacja AiSD (3)](https://user-images.githubusercontent.com/49908210/167669507-995ca541-18bc-42cd-9f40-2aca0411ced4.svg)
![Prezentacja AiSD (4)](https://user-images.githubusercontent.com/49908210/167669530-cccf17bf-201f-4d37-aa3c-b14db1304ddc.svg)
![Prezentacja AiSD (5)](https://user-images.githubusercontent.com/49908210/167669533-e4721897-2f27-4ca4-8771-4d88e8fa0049.svg)
![Prezentacja AiSD (6)](https://user-images.githubusercontent.com/49908210/167669544-000914d1-3b00-4f69-a9cd-240a4e240c0d.svg)
![Prezentacja AiSD (7)](https://user-images.githubusercontent.com/49908210/167669555-934f5e6f-a9b0-4463-86d8-cf2c710e1534.svg)
![Prezentacja AiSD (8)](https://user-images.githubusercontent.com/49908210/167669561-54732867-8ebf-4b27-8bc8-caffb13b7f9d.svg)
![Prezentacja AiSD (9)](https://user-images.githubusercontent.com/49908210/167669576-77b40790-d098-43c2-91a0-4692060ca998.svg)
![Prezentacja AiSD (10)](https://user-images.githubusercontent.com/49908210/167669581-cced6412-4aea-4a72-94dd-93bd3f3127b0.svg)
![Prezentacja AiSD (11)](https://user-images.githubusercontent.com/49908210/167669589-53294c64-41c4-40b1-89d8-6a9e850c9261.svg)
![Prezentacja AiSD (12)](https://user-images.githubusercontent.com/49908210/167669605-3913d47c-1a6d-4d22-aa98-8793a60ac48e.svg)
![Prezentacja AiSD (13)](https://user-images.githubusercontent.com/49908210/167669613-0d3a3193-41cf-4cbf-a767-9daaeeec6c10.svg)
![Prezentacja AiSD (14)](https://user-images.githubusercontent.com/49908210/167669627-535da503-656a-4a7b-ab52-fd63b97beea4.svg)
![Prezentacja AiSD (15)](https://user-images.githubusercontent.com/49908210/167669641-b889aef9-8ea0-4209-9032-0918d7e3ab72.svg)
![Prezentacja AiSD (16)](https://user-images.githubusercontent.com/49908210/167669651-255231ac-2ce0-453a-baf1-959deb6ef622.svg)

## Najwa??niejsze foldery i ich przeznaczenie

* Benchmarks - Projekt zawieraj??cy implementacje benchmark??w
  * bench_main.cpp - Punkt wej??ciowy Benchmark??w i ich wywo??ywanie
  * BenchmarkBase.h - Implementacja narz??dzi do benchmarkowania
* BenchOutput - Wyniki benchmark??w
  * Bench i7 7700k - Wyniki na procesorze i7 7700k
    * Foldery benchmark??w
      * NAZWA_BENCHMARKU 
         * `*.csv` 
         * `quick_lookup.py` - Skrypt agreguj??cy dane w folderze (pliki CSV)
         * `Figure_1.png` - Prosta wizualizacja benchmarka
* ProjectDisjointSets - Projekt zawieraj??cy implementacje DisjointSet??w
  * `main.cpp` - Punkt wej??ciowy do projektu (Proste przedstawienie dzia??ania Implementacji)
  * `DisjointSetBase.h` - Plik zawieraj??cy definicje interfejs??w u??ytch w projektach
  * Implementations - Implementacje zbior??w roz????cznych
    * `DisjointSetList.h` - Implementacja listowa
    * `DisjointSetTrees.h` - Implementacja metod?? Lasu
    * `DisjointSetMap.h` - Naiwna implementacja z u??yciem mapy
    * `DisjointSetTreesCom.h` - Implementacja Lasem z kompresj?? ??cie??ki
    * `DisjointSetTreesComRan.h`  - Implementacja Lasem z rang?? i kompresj?? ??cie??ki 
    * `DisjointSetTreesRan.h` - Implementacja Lasem z rang?? 
* Tests - Projekt zawieraj??cy testy
  * `test_main.cpp` - Main test??w i ich implementacja
  * `TestOutput.png` - Wynik dzia??ania projektu
