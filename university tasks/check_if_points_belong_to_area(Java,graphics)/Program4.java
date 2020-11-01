import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.event.ChangeEvent;
import java.util.LinkedList;
import java.util.*;

import javax.swing.event.ChangeListener;

class Program4 {
    private static float x, y;
    private static Rendering render;
    private static JPanel toolPanel;

    private static JComboBox combobox;
    private static JSpinner spinner;
    private static JLabel xLabel;
    private static JLabel yLabel;
    private static JRadioButton rbutton;

    public static void RenderingRepaint(){
        render.repaint();
    }



    public static void main(String[] args){
        JFrame frame = new JFrame("791");
        frame.setLayout(new GridLayout(2, 1));
        frame.setSize(500, 700);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        render = new Rendering(10);
        frame.add(render);

        render.addMouseListener(new MouseAdapter(){
            public void mousePressed(MouseEvent e) {
                x = render.pixelsToX(e.getX());
                y = render.pixelsToY(e.getY());
                xLabel.setText("x: " + String.format("%.2f", x));
                yLabel.setText("y: " + String.format("%.2f", y));
                render.addNewPoint(x, y);
            }});

        toolPanel = new JPanel();
        toolPanel.setLayout(new GridLayout(2,10));
        frame.add(toolPanel);

        toolPanel.add(xLabel = new JLabel("x: "));
        toolPanel.add(yLabel = new JLabel("y: "));

        toolPanel.add(new JLabel("Radius: "));
        Float[] radius = {5f, 6f, 7f, 8f, 9f, 10f, 11f, 12f, 13f, 14f, 15f};
        SpinnerModel model = new SpinnerListModel(radius);
        spinner = new JSpinner(model);
        spinner.setValue(10f);
        toolPanel.add(spinner);

        spinner.addChangeListener(new ChangeListener(){
            public void stateChanged(ChangeEvent e) {
                JSpinner source = (JSpinner)e.getSource();
                render.setR((float)source.getValue());
                render.addAnimatedPoint(x, y);
            }});

        toolPanel.add(new JLabel("Select X: "));
        String[] data = {"-5", "-4", "-3", "-2", "-1", "0", "1", "2", "3", "4", "5"};
        combobox = new JComboBox(data);
        combobox.setSelectedItem("0");
        toolPanel.add(combobox);

        toolPanel.add(new JLabel("Select Y: "));
        ButtonGroup group = new ButtonGroup();
        for(Integer i = 0; i < 5; i++){
            rbutton = new JRadioButton(i.toString());
            group.add(rbutton);
            if (i == 0) rbutton.setSelected(true);
            toolPanel.add(rbutton);
        }

        JButton button = new JButton("Add point");
        button.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                Enumeration<AbstractButton> b = group.getElements();
                String y = "", x;
                while(b.hasMoreElements())
                {
                    JRadioButton temp = (JRadioButton)b.nextElement();
                    if(temp.isSelected()) y = temp.getText();
                }
                x = combobox.getSelectedItem().toString();
                xLabel.setText("x: " + x);
                yLabel.setText("y: " + y);
                render.addNewPoint(Float.valueOf(x), Float.valueOf(y));
            }});
        toolPanel.add(button);

        frame.setVisible(true);
    }
}

class Rectangle{
    public float x, y;
    public float width, height;

    public float getX() {
        return x;
    }

    public float getY() {
        return y;
    }

    public float getWidth() {
        return width;
    }

    public float getHeight() {
        return height;
    }

    Rectangle(float x, float y, float width, float height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    public boolean hitInArea(Punctum a, float R) {
        float xPunctum = a.getX();
        float yPunctum = a.getY();

        x = 0; y = R; width = R/2; height = R;

        if((xPunctum > x) && (xPunctum < (x + width)) && (yPunctum < y) && (yPunctum > (y - height)))
            return true;
        else return false;
    }

    public boolean hitOnBorder(Punctum a, float R) {
        float xPunctum = a.getX();
        float yPunctum = a.getY();

        x = 0; y = R; width = R/2; height = R;

        if(((xPunctum == x) && (yPunctum <= y) && (yPunctum >= y - height)) || ((xPunctum == x + width) && (yPunctum <= y) && (yPunctum >= y - height)) ||
                ((yPunctum == y) && (xPunctum >= x) && (xPunctum <= x + width)) || ((yPunctum == y - height) && (xPunctum >= x) && (xPunctum <= x + width)))
            return true;
        else return false;
    }
}

class Triangle{
    private Punctum A;
    private Punctum B;
    private Punctum C;

    public Punctum getA() {
        return A;
    }

    public Punctum getB() {
        return B;
    }

    public Punctum getC() {
        return C;
    }

    Triangle(Punctum A, Punctum B, Punctum C) {
        this.A = A;
        this.B = B;
        this.C = C;
    }

    public boolean hitInArea(Punctum a, float R) {
        B = new Punctum(-R,0); C = new Punctum(0, R);
        float ABCSquare = Square(A, B, C);

        float ABDSquare = Square(A, B, a);
        float BCDSquare = Square(B, C, a);
        float CADSquare = Square(C, A, a);
        float Sum = ABDSquare + BCDSquare + CADSquare;

        if(Math.abs((ABCSquare - Sum)) <= 0.01) return true;
        else return false;
    }

    private float GetSide(float x1, float y1, float x2, float y2) {
        return (float)Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
    }

    private float Square(Punctum A, Punctum B, Punctum C) {
        float a = GetSide(A.getX(), A.getY(), B.getX(), B.getY());
        float b = GetSide(B.getX(), B.getY(), C.getX(), C.getY());
        float c = GetSide(C.getX(), C.getY(), A.getX(), A.getY());
        float p = a + b + c;

        p /= 2.0f;

        return (float)Math.sqrt(p * (p - a) * (p - b) * (p - c));
    }

    public boolean hitOnBorder(Punctum a, float R) {
        B = new Punctum(-R,0); C = new Punctum(0, R);
        float ABDSquare = Square(A, B, a);
        float BCDSquare = Square(B, C, a);
        float CADSquare = Square(C, A, a);

        if((ABDSquare <= 0.01 || BCDSquare <= 0.01 || CADSquare <= 0.01) && hitInArea(a, R))
            return true;
        else return false;
    }
}

class Circle{
    public float radius;

    public float getRadius() {
        return radius;
    }

    Circle(float radius) {
        this.radius = radius;
    }

    public boolean hitInArea(Punctum Punctum, float R) {
        radius = R/2;
        float xPunctum = Punctum.getX();
        float yPunctum = Punctum.getY();
        boolean inside = false;

        if (((xPunctum != 0) && (yPunctum != 0)) && (xPunctum < 0) && (yPunctum < 0) && ((Math.pow(xPunctum, 2) + Math.pow(yPunctum, 2)) < Math.pow(radius, 2)))
            return true;
        else return false;
    }

    public boolean hitOnBorder(Punctum Punctum, float R) {
        radius = R/2;
        float xPunctum = Punctum.getX();
        float yPunctum = Punctum.getY();
        boolean onBorder = false;

        if ((xPunctum <= 0) && (yPunctum <= 0) && (Math.pow(xPunctum, 2)) + Math.pow(yPunctum, 2) <= Math.pow(radius, 2))
            return true;
        else return false;
    }
}

class Rendering extends JPanel {
    private LinkedList<Punctum> points;
    private float radius;
    private int scale = 40;
    Rectangle rect;
    Triangle triang;
    Circle circ;

    LinkedList<AnimatedPunctum> listAnimatedPunctum = new LinkedList<AnimatedPunctum>();

    Rendering(float R) {
        points = new LinkedList<Punctum>();
        radius = R;
    }

    private void addPoint(float px, float py) {
        points.add(new Punctum(pixelsToX(px), pixelsToY(py),false));
    }

    private void addPoint(float x, float y, boolean outside) {
        points.add(new Punctum(x, y, outside));
    }

    private boolean hitInArea(Punctum a) {
        boolean inside = false;

        if(rect.hitInArea(a, radius)) inside = true;
        if(triang.hitInArea(a, radius)) inside = true;
        if(circ.hitInArea(a, radius)) inside = true;

        if(rect.hitOnBorder(a, radius)) inside = true;
        if(triang.hitOnBorder(a, radius)) inside = true;
        if(circ.hitOnBorder(a, radius)) inside = true;

        return inside;
    }

    public void addNewPoint(float xx, float yy) {
        if(!hitInArea(new Punctum(xx, yy))) {
            addPoint(xx, yy, true);
            this.repaint();
        }
        else {
            addPoint(xx, yy, false);
            this.repaint();
        }
    }

    public void addAnimatedPoint(float xx, float yy) {
        if (!points.isEmpty())
            for (int i = 0; i < points.size(); i++) {
                if (points.get(i).isOutside() && hitInArea(points.get(i))) {
                    listAnimatedPunctum.add(new AnimatedPunctum(points.get(i).getX(),points.get(i).getY()));
                    points.get(i).outside = false;
                    listAnimatedPunctum.get(listAnimatedPunctum.size() - 1).start();
                    points.remove(i);
                }
            }
    }

    public void setR(float R) {
        if (R!=radius) scale += scale*(R - radius)/radius;
        radius = R;
        repaint();
    }

    public float xToPixels(float x) {
        int m = getWidth() / 2;
        return (m * (1 + x * 2 / scale));
    }

    public float yToPixels(float y) {
        int m = getHeight() / 2;
        return (m * (1 - y * 2 / scale));
    }

    public float pixelsToX(float p) {
        float m = getWidth() / 2;
        return (p - m) / m * scale / 2;
    }

    public float pixelsToY(float p) {
        float m = getHeight() / 2;
        return (m - p) / m * scale / 2;
    }

    private void drawEmergingPoint(Graphics g) {
        if (!listAnimatedPunctum.isEmpty()) {
            for (int i = 0; i < listAnimatedPunctum.size(); i++) {
                if (listAnimatedPunctum.get(i).getRadius() >= 8){
                    addPoint(xToPixels(listAnimatedPunctum.get(i).getX()), yToPixels(listAnimatedPunctum.get(i).getY()));
                    listAnimatedPunctum.remove(i);
                }
                else {
                    if (hitInArea(new Punctum(((listAnimatedPunctum.get(i).getX())), (listAnimatedPunctum.get(i).getY())))) g.setColor(Color.BLACK);
                    else g.setColor(Color.WHITE);

                    g.fillOval((int)xToPixels(listAnimatedPunctum.get(i).getX())-(int)listAnimatedPunctum.get(i).getRadius()/2,(int)yToPixels(listAnimatedPunctum.get(i).getY())-(int)listAnimatedPunctum.get(i).getRadius()/2,(int)listAnimatedPunctum.get(i).getRadius(),(int)listAnimatedPunctum.get(i).getRadius());
                }
            }
        }
    }

    private void drawGraphBody(Graphics g) {
        float buffer1 = this.radius;
        int buffer2 = this.scale;
        this.radius = 10;
        this.scale = 40;

        rect = new Rectangle(0, radius, radius/2, radius);
        circ = new Circle(radius/2);
        triang = new Triangle(new Punctum(0, 0), new Punctum(-radius, 0), new Punctum(0, radius));

        g.setColor(new Color(0, 0, 255));

        g.fillRect((int)xToPixels(rect.getX()), (int) yToPixels(rect.getY()), (int)xToPixels(rect.getWidth()) - (int)xToPixels(0) + 1, (int)yToPixels(0) - (int)yToPixels(rect.getHeight()));

        int[] xPoints = {(int)xToPixels(triang.getA().getX()), (int)xToPixels(triang.getB().getX()), (int)xToPixels(triang.getC().getX())};

        int[] yPoints = {(int)yToPixels(triang.getA().getY()), (int)yToPixels(triang.getB().getY()), (int)yToPixels(triang.getC().getY())};

        g.fillPolygon(xPoints, yPoints, 3);

        g.fillArc((int)xToPixels(-circ.getRadius()),
                (int)yToPixels(circ.getRadius()),
                2 * (int)(xToPixels(circ.getRadius()) - xToPixels(0)) + 1,
                2 * (int)(yToPixels(-circ.getRadius()) - yToPixels(0)) + 1,
                180,
                90);

        g.setColor(Color.BLACK);
        g.drawLine(0, (int)yToPixels(0), this.getWidth(), (int)yToPixels(0));
        g.drawLine((int)xToPixels(0), this.getHeight(), (int)xToPixels(0), 0);

        this.radius = buffer1;
        this.scale = buffer2;
    }

    private void drawAddedPoints(Graphics g) {
        for (Punctum p : points)
            if (hitInArea(p)) {
                p.outside = false;
                g.setColor(Color.BLACK);
                g.fillOval((int)xToPixels(p.getX()) - 8 / 2, (int)yToPixels(p.getY()) - 8 / 2, 8, 8);
            }else {
                p.outside = true;
                g.setColor(Color.WHITE);
                g.fillOval((int)xToPixels(p.getX()) - 8 / 2, (int)yToPixels(p.getY()) - 8 / 2, 8, 8);
            }
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        setBackground(new Color(0, 255, 150));
        drawGraphBody(g);
        drawAddedPoints(g);
        drawEmergingPoint(g);

    }
}

class AnimatedPunctum extends Thread {
    private final float x;
    private final float y;
    private float radius;

    public float getX() {
        return x;
    }

    public float getY() {
        return y;
    }

    public float getRadius() {
        return radius;
    }

    AnimatedPunctum(float x, float y) {
        this.x = x;
        this.y = y;
        this.radius = 1;
    }

    public void run() {
        for(int i = 0; i < 30; i++) {
            this.radius += 0.25;

            try {
                Thread.sleep(100);

            } catch (Exception e) {
                System.out.println("Punctum Animation failed");
            }

            Program4.RenderingRepaint();
        }
    }
}

class Punctum {
    private final float x;
    private final float y;
    public boolean outside;

    public Punctum(float x, float y, boolean outside) {
        this.x = x;
        this.y = y;
        this.outside = outside;
    }

    public Punctum(float x, float y) {
        this.x = x;
        this.y = y;
        this.outside = true;
    }

    public float getX() { return x; }

    public float getY() {
        return y;
    }

    public boolean isOutside() {
        return outside;
    }
}