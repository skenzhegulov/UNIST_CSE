#lang racket
;Course:     Programming Languages (CSE34101)
;Name:       Saken Kenzhegulov
;Student ID: 20132027

;P2

;3.1 Named Let
(define (my-loop a b c)
  (let sum((s 0) (i a))
      (if (>= i b) s
          (sum (+ s i) (+ i c)))))

;3.2 Scheme Interpreter
(define (my-eval expr)
  (let ev ((x expr))
    (if (number? x) x
        (begin
          (let ((op +) (o (car x))(a (ev(car (cdr x))))(b (ev(car (cdr (cdr x))))))
            (cond ((eqv? o '-) (set! op -))
                  ((eqv? o '*) (set! op *))
                  ((eqv? o '/) (set! op /)))
            (op a b))
    ))))
