#lang racket

;Course:     Programming Languages (CSE34101)
;Name:       Saken Kenzhegulov
;Student ID: 20132027

(define (sqrt x) (sqrt-iter 1.0 x))

(define (sqrt-iter guess x) 
 	(new-if (good-enough? guess x)
        	guess
		(sqrt-iter (improve guess x) x)))

(define (improve x y) 
	(- x (/ (- (* x x) y) (* 2 x))))

(define (good-enough? x y) 
 	(if (< (abs (- (* x x) y)) 0.0001) #t #f))

(define (new-if c a b)
	(cond (c a) (else b)))
