```bash
cmake -S . -B build -DBUILD_SHARED_LIBS=ON -DWLIB_BUILD_DOCS=ON -DWLIB_OPTION=ON
cmake --install build --prefix installdir
```