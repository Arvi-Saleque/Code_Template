const int ITER = 100; // select the number of iterations
int32_t main() {  
  string correct = "g++ -o correct correct.cpp";
  system(correct.c_str()); // compiling the correct solution
  string wrong = "g++ -o wrong wrong.cpp";  
  system(wrong.c_str()); // compiling the wrong solution
  string generator = "g++ -o generator generator.cpp"; 
  system(generator.c_str()); // compiling the generator
  for (int t = 1; t <= ITER; t++) {
    cerr << "try" << t << "-\n";
    string in = "input.txt";
    string generator = "./generator > input.txt";
    system(generator.c_str()); // generating a case
    string correct_solution = "./correct < input.txt > correct_solution.txt";
    system(correct_solution.c_str());
    string wrong_solution = "./wrong < input.txt > wrong_solution.txt";
    system(wrong_solution.c_str());
    ifstream correct_file;
    correct_file.open("correct_solution.txt"); //opening correct solution file
    string correct_output = "", line;
    while (getline(correct_file, line, '.')) {  
      correct_output += line;
    }
    ifstream wrong_file;
    wrong_file.open("wrong_solution.txt"); //opening wrong solution file
    string wrong_output = "";
    while (getline(wrong_file, line, '.')) { 
      wrong_output += line;
    }
    if (correct_output != wrong_output) {
      cout << "MISMATCH " << t << "\n\n";
      return 0;
    }
    correct_file.close();
    wrong_file.close();
  }
  cout << "No cases found!\n";
  return 0;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); 
long long get_rand(long long l, long long r) { 
  if(l > r) swap(l, r);
  return l + rnd() % (r - l + 1);
}

{
    "cmd": ["g++ $file -o $file_base_name && ./$file_base_name < input.txt "],
    "shell": true,
    "selector": "source.c, source.c++",
    "path": "/usr/bin",
    "working_dir": "$file_path"
}