#include <stdio.h>
#include <stdlib.h>

// Define the structure for a Point
struct Point {
    int x, y;
};

struct Point p0;

struct Point nextToTop(struct Point stack[], int *top) {
    struct Point p = stack[*top];
    (*top)--;
    struct Point res = stack[*top];
    (*top)++;
    return res;
}

void swap(struct Point *p1, struct Point *p2) {
    struct Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int distSq(struct Point p1, struct Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(struct Point p, struct Point q, struct Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2) {
    struct Point *p1 = (struct Point *)vp1;
    struct Point *p2 = (struct Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

void push(struct Point stack[], int *top, struct Point p, int maxSize) {
    if (*top == maxSize - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++(*top)] = p;
}

struct Point pop(struct Point stack[], int *top) {
    if (*top == -1) {
        printf("Stack underflow\n");
        struct Point nullPoint = {-1, -1}; // Return a dummy point on underflow
        return nullPoint;
    }
    return stack[(*top)--];
}

void convexHull(struct Point points[], int n) {
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    swap(&points[0], &points[min]);

    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(struct Point), compare);

    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
            i++;
        }
        points[m] = points[i];
        m++;
    }

    if (m < 3) return;

    struct Point stack[m];
    int top = -1;
    int maxSize = m;
    push(stack, &top, points[0], maxSize);
    push(stack, &top, points[1], maxSize);
    push(stack, &top, points[2], maxSize);

    for (int i = 3; i < m; i++) {
        while (top > 0 && orientation(nextToTop(stack, &top), stack[top], points[i]) != 2) {
            pop(stack, &top);
        }
        push(stack, &top, points[i], maxSize);
    }

    while (top >= 0) {
        struct Point p = pop(stack, &top);
        printf("(%d, %d)\n", p.x, p.y);
    }
}

int main() {
    // struct Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
    //                          {0, 0}, {1, 2}, {3, 1}, {3, 3}};

    struct Point points[] = {{5,5}, {1,1}, {4,0}, {2,2}, {0,4}};
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}
