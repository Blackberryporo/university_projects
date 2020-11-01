public class Program3 {

    public static void main(String[] args) {
        double R = 0;
        try {
            if ( args.length > 1 ) throw new Exception();
            R = new Double(args[0]);
            if ( R < 0 ) throw new Exception();
        } catch (Exception exception) {
            System.out.println("Exception: Invalid argument format (should be one positive double argument)");
            System.exit(1);
        }
        System.out.println("R = "+R);
        PointsCollection puncta = new PointsCollection();
        puncta.PrintWholePointsCollection();
        System.out.println("Points included in the area:");
        puncta.PrintPointsCollection(R);
    }
}

class Punctum {

    private float x;
    private float y;

    Punctum(float x, float y){
        this.x = x;
        this.y = y;
    }

    public float ReturnX(){
        return(this.x);
    }

    public float ReturnY(){
        return(this.y);
    }

}

class Kontur {
    private double R;
    private float x;
    private float y;

    Kontur(double R, float x, float y){
        this.R = R;
        this.x = x;
        this.y = y;
    }

    public boolean IsInsideArea(){
        if ( -R < x && x < 0 && -R < y && y < 0 || (x > 0 || x == 0) && (y < 0 || y == 0) && x*x + y*y < R*R && !(x == 0 && y == 0) || y > 0 && y < R/2 && x > 0 && x < R && x + 2*y < R)
        return true;
        else return false;
    }
}

class PointsCollection {

    private java.util.LinkedHashSet<Punctum> points;
    private java.util.Iterator<Punctum> pointsIterator;
    private int capacity = 9;

    private void CreatePointsCollection(){
        points.add(new Punctum(3,3));
        points.add(new Punctum(5,-5));
        points.add(new Punctum(1,3));
        points.add(new Punctum(-1,1));
        points.add(new Punctum(-4,5));
        points.add(new Punctum(-1,-2));
        points.add(new Punctum(0,0));
        points.add(new Punctum(1,3));
        points.add(new Punctum(-4,-4));
    }

    PointsCollection(){
        this.points = new java.util.LinkedHashSet<Punctum>(this.capacity);
        this.CreatePointsCollection();
    }

    public void PrintPointsCollection(double R){
        this.pointsIterator = points.iterator();
        do {
            if (pointsIterator.hasNext() == false) break;
                Punctum buffer = pointsIterator.next();
                Kontur area = new Kontur(R, buffer.ReturnX(), buffer.ReturnY());
            if (area.IsInsideArea()) System.out.format("x = %+.2f\t\ty = %+.2f %n", buffer.ReturnX(),buffer.ReturnY());
        } while (true);
    }

    public void PrintWholePointsCollection(){
        this.pointsIterator = points.iterator();
        do {
            if (pointsIterator.hasNext() == false) break;
            Punctum buffer = pointsIterator.next();
            System.out.format("x = %+.2f\t\ty = %+.2f %n", buffer.ReturnX(),buffer.ReturnY());
        } while (true);
    }
}

