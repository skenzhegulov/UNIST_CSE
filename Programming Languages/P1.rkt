#lang racket
;Course:     Programming Languages (CSE34101)
;Name:       Saken Kenzhegulov
;Student ID: 20132027

;P1

;Problem 1
 (define what-kind (lambda (a b c) 
                     (if (= a 0) 'degenerate
                           (cond ((< (- (* b b) (* 4 (* a c))) 0) 'none)
                                 ((= (- (* b b) (* 4 (* a c))) 0) 'one)
                                 ((> (- (* b b) (* 4 (* a c))) 0) 'two)))))

;Problem 2
  (define move (lambda (s x y)
                 (if (eqv? s 'forward) (min 99 (+ y x)) (max 0 (- y x)))))

;Problem 3
 (define dollar-store? (lambda (lis)
    (cond ((null? lis) #t)
          ((< 1 (car lis)) #f)
          (else (dollar-store? (cdr lis))))))

;Problem 4
 (define prices-below-threshold? (lambda (threshold lis)
    (cond ((null? lis) #t)
          ((< threshold (car lis)) #f)
          (else (prices-below-threshold? threshold (cdr lis))))))

;Problem 5
(define reverse-list (lambda (lis)
  (if (null? lis) '() (append (reverse-list (cdr lis)) (list (car lis))))))

;Problem 6
(define deep-reverse (lambda (lis)
  (if (list? lis) (reverse-list (map deep-reverse lis)) lis)))

;Problem 7
(define is-included? (lambda(x lis oper) 
    (cond ((null? lis) #f)
          ((oper x (car lis)) #t)
          (else (is-included? x (cdr lis) oper)))))

;Problem 8
(define my-append (lambda(lis x)
  (foldr cons (list x) lis)))