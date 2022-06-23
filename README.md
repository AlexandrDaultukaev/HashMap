# HashMap

My educational implementation HashMap(unordered_map)

Example:

```
HashMap<std::string, int> hm;
    hm["31"] = 1;
    hm["32"] = 2;
    hm["33"] = 3;
    for (Iterator<std::string, int> it = hm.begin(); it != hm.end(); it++) {
         std::cout << it->first << ": " << it->second << "\n";
    }
```

Output:

```
31: 1
32: 2
33: 3
```

You can use your own hash function:

```
struct Myhash {
  std::size_t operator()(const std::string &k) const {

     return std::hash<std::string>()(k) << 1U;
  }
};

HashMap<std::string, int, Myhash> hm;

hm["31"] = 1;
hm["32"] = 2;
hm.set_value("33", 3);
```
