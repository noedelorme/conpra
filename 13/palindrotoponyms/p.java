import java.util.HashSet;
import java.util.Locale;
import java.util.Scanner;
import java.util.Set;

public class G {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in).useLocale(Locale.ENGLISH);

    int t = sc.nextInt();
    for (int i = 1; i <= t; i++) {

      int n = sc.nextInt();
      int p = sc.nextInt();

      Set<Pair> is = findAllPalindromesUsingCenter(sc.next(), p);
      System.out.print("Case #" + i + ": ");
      if (is.isEmpty()) {
        System.out.println("none");
      } else {
        Pair first = is.iterator().next();
        System.out.println(first.left + " " + first.right);
      }

    }
  }

  static class Pair implements Comparable<Pair> {

    Integer left;
    Integer right;

    Pair(Integer left, Integer right) {
      this.left = left;
      this.right = right;
    }

    @Override
    public int compareTo(Pair o) {
      return o.left - this.left;
    }
  }

  //From: https://www.baeldung.com/java-palindrome-substrings
  static Set<Pair> findAllPalindromesUsingCenter(String input, int minimum) {
    Set<Pair> palindromes = new HashSet<>();
    for (int i = 0; i < input.length(); i++) {
      palindromes.addAll(findPalindromes(input, i, i + 1, minimum));
      palindromes.addAll(findPalindromes(input, i, i, minimum));
      if(!palindromes.isEmpty()){
        return palindromes;
      }
    }
    return palindromes;
  }

  static Set<Pair> findPalindromes(String input, int low, int high, int minimum) {
    Set<Pair> result = new HashSet<>();
    while (low >= 0 && high < input.length() && input.charAt(low) == input.charAt(high)) {
      String pos = input.substring(low, high + 1);
      if (pos.length() >= minimum) {
        result.add(new Pair(low + 1, high + 1));
      }
      low--;
      high++;

    }
    return result;
  }


}
