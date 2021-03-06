(begin 
    (define make-point (lambda (x y)  (set-property "object-name" "point" (set-property "size" 0 (list x y))) ))
    (define make-line (lambda (p1 p2) (set-property "object-name" "line"  (set-property "thickness" 1 (list p1 p2))) ))
    (define make-text (lambda (str)   (set-property "object-name" "text"  (set-property "position" (make-point 0 0) str)) ))
    (define discrete-plot (lambda (DATA OPTIONS) (set-property "object-name" "discrete-plot" (list DATA OPTIONS))))
    (define continuous-plot (lambda (FUNC BOUNDS OPTIONS) (set-property "object-name" "continuous-plot" (list FUNC BOUNDS OPTIONS))))
)
