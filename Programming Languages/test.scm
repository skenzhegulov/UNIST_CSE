#lang racket

(begin
  (define add2 (lambda (x y) (* x y)))
  (add2 4 5)
  (add2 9 5)
  )

(begin
  (define p 80)
  (if (> p 70) 'safe 'unsafe)
  (if (< p 90) 'low-pressure 'norm)
  )

(begin
  (define c #\d)
  (if (char<? c #\c) -1
      (if (char=? c #\c) 0
          1))
  )

(begin
  (define x 0)
  (set! x 20)
  (let* ((x 1)
        (y x))
    (+ x y))
  )

(begin
  (define even? (lambda (n)
                  (if (= n 0) #t
                      (odd? (- n 1)))))
  (define odd? (lambda (n)
                 (if (= n 0) #f
                     (even? (- n 1)))))
  (odd? 23)
  )

(begin
  (define f 1)
  (define fact (lambda (n)
                 (set! f (* f n))
                 (if (< n 2) f
                     (fact (- n 1)))))
  (fact 5)
  )

(begin
  (letrec ((countdown (lambda (i)
                        (if (= i 0) 'litoff
                            (begin (display i)
                                   (newline)
                                   (countdown (- i 1)))))))  
  (countdown 10))
  )

(begin
  (let countdown ((i 10))
                        (if (= i 0) 'litoff
                            (begin (display i)
                                   (newline)
                                   (countdown (- i 1)))))
  )

(begin
  (define add3 (lambda (x) (+ x 2)))
  (map add3 '(1 2 3))
  (for-each display (list "one" "two"))
  (map + '(1 2 3) '(10 20 30))
  (map cons '(1 2 3) '(10 20 30))
  )
