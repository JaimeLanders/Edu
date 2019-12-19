import java.io.*;
import java.util.*;

class Example {
  public static void main(String argv[]) throws IOException {
    double[] ds       = readDoubleArray(argv[0]);
    int b             = Integer.parseInt(argv[1]);
    double min        = Double.parseDouble(argv[2]);
    double max        = Double.parseDouble(argv[3]);
//    double mean       = mean(ds);
    histogram(ds, b, min, max);
//    System.out.println("mean = " + mean + " variance = " + variance + " stdev = " + stdev);
  }

/*  private static double mean(double[] ds) {
    double sum = 0.0;
    for (double d : ds) {
      sum += d;
    }
    return sum/ds.length;
  }
*/
  private static void histogram(double[] ds, int b, double min, double max) {
//    System.out.println("b = " + b); // DEBUG
//    System.out.println("min = " + min); // DEBUG
//    System.out.println("max = " + max); // DEBUG
    double binSize = (max - min) / b;
    int binCount = 0;
    System.out.println("binSize = " + binSize); // DEBUG

    for(double binIndex = min - binSize; binIndex <= max; binIndex += binSize){
//    for(double binIndex = min; binIndex <= max; binIndex += binSize){
//      System.out.println("binIndex = " + binIndex); // DEBUG
      for (double d : ds) {
//      System.out.println("d = " + d); // DEBUG

        if (d >= binIndex && d <= binIndex + binSize){
//        if (d >= min && d <= max && d >){
          binCount += 1;
        }
        else if (binIndex < min && d < min){
          binCount += 1;
        }
//        else if (d > max)
//          binCount += 1;
      }
      if(binIndex >= min && binIndex <= binIndex + binSize)
        System.out.println(binIndex + " <= x < " + (binIndex + binSize) + ": " + binCount);
      else if (binIndex < min)
        System.out.println("x < " + (binIndex + binSize) + ": " + binCount);
      else if (binIndex > binIndex)
        System.out.println("x >= " + (binIndex + binSize) + ": " + binCount);
      binCount = 0;
    }
  }

  private static double[] readDoubleArray(String filename) throws IOException {
    FileReader f = new FileReader(filename);
    Scanner sc = new Scanner(f);
    int n = sc.nextInt();
    double[] ds = new double[n];
    for (int i = 0; i < n; i++) {
      ds[i] = sc.nextDouble();
    }
    f.close();
    return ds;
  }
}
