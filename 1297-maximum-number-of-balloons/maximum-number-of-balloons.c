int maxNumberOfBalloons(char *text) {
    int freq[26] = {0};

    for (int i = 0; text[i] != '\0'; i++) {
        freq[text[i] - 'a']++;
    }

    int b = freq['b' - 'a'];
    int a = freq['a' - 'a'];
    int l = freq['l' - 'a'] / 2;
    int o = freq['o' - 'a'] / 2;
    int n = freq['n' - 'a'];

    int ans = b;
    if (a < ans) ans = a;
    if (l < ans) ans = l;
    if (o < ans) ans = o;
    if (n < ans) ans = n;

    return ans;
}