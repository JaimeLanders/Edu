class Example {
  public static void main(String argv[]) {
    if (argv.length < 2) {
      usage();
    } else {
      int n = 0;
      try {
        n = Integer.parseInt(argv[0]);
      } catch (NumberFormatException e) {
        usage();
      }
      for (int i = 0; i < n; i++) {
        System.out.print(i +  ": ");
        for (int  j = 1; j < argv.length; j++) {
          System.out.print(argv[j] + " ");
        }
        System.out.println();
      }
    }
  }

  private static void usage() {
    System.err.println("usage: java Example count string");
    System.exit(1);
  }
}
