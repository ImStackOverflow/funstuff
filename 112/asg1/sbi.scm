#!/afs/cats.ucsc.edu/courses/cmps112-wm/usr/racket/bin/mzscheme -qr
;; $Id: sbi.scm,v 1.3 2016-09-23 18:23:20-07 - - $
;;
;; NAME
;;    sbi.scm - silly basic interpreter
;;
;; SYNOPSIS
;;    sbi.scm filename.sbir
;;
;; DESCRIPTION
;;    The file mentioned in argv[1] is read and assumed to be an SBIR
;;    program, which is the executed.  Currently it is only printed.
;;

(define *stderr* (current-error-port))

;makes a label table
(define *label-table* (make-hash))
;retrieves from label table
(define (label-get key)
        (hash-ref *label-table* key))
;puts into label table
(define (label-put! key value)
        (hash-set! *label-table* key value))
		
;makes varriable table
(define *varriable-table* (make-hash))
;retrieves from varriable table
(define (varriable-get key)
        (hash-ref *varriable-table* key))
(define (varriable-put! key value)
        (hash-set! *varriable-table* key value))
		
		
;makes function table
(define *function-table* (make-hash))
(define (function-get key)
        (hash-ref *function-table* key))
(define (function-put! key value)
        (hash-set! *function-table* key value))

;evaluates if statment relop
;returns true or false value		
(define (comparison relop exp1 exp2)
		(case (relop)
			((= exp1 exp2) '=)
			((< exp1 exp2) '<)
			((> exp1 exp2) '>)
			((not (= exp1 exp2)) '<>)
			((>= exp1 exp2) '>=)
			((<= exp1 exp2) '<=)))

;checks if statement
;if statment is true then returns label
(define (if-statement relop exp1 exp2 label)
	(if (comparison relop exp1 exp2)
		(label)
		()))
			
;let function to define varriables in variable-table
;type true if array, false if symbol
(define (let-function varriable value index type)
	(if (type);checks if array
		(if (vector? varriable-get varriable);check to make sure is array
			(vector-set! varriable index value);set index to value
			(die '("non-vector returned in let-function")));error out if not array
		(variable-put varriable value)));puts varriable into symbol table

	
(for-each
    (lambda (pair)
            (function-put! (car pair) (cadr pair)))
    `(
		(dim    ,(lambda (x y) (variable-put! x (make-vector y))));creates an array of y dimension
		(let    ,(lambda (var val i type) (let-function var val i type)));assigns varriables
		(goto   ,(lambda (x) (label-get x)));returns label data from label-table*
		(if     ,(lambda (relop exp1 exp2 label) (if-statement relop exp1 exp2 label)));if statement
		(print  ,(lambda (x) (display x)));print statement
		(input )
        (log10_2 0.301029995663981195213738894724493026768189881)
        (sqrt_2  1.414213562373095048801688724209698078569671875)
        (e       2.718281828459045235360287471352662497757247093)
        (pi      3.141592653589793238462643383279502884197169399)
        (div     ,(lambda (x y) (floor (/ x y))))
        (log10   ,(lambda (x) (/ (log x) (log 10.0))))
        (mod     ,(lambda (x y) (- x (* (div x y) y))))
        (quot    ,(lambda (x y) (truncate (/ x y))))
        (rem     ,(lambda (x y) (- x (* (quot x y) y))))
        (+       ,+)
        (^       ,expt)
        (ceil    ,ceiling)
        (exp     ,exp)
        (floor   ,floor)
        (log     ,log)
        (sqrt    ,sqrt)

     ))


(define *run-file*
    (let-values
        (((dirpath basepath root?)
            (split-path (find-system-path 'run-file))))
        (path->string basepath))
)

;kills program and spits error message
(define (die list)
    (for-each (lambda (item) (display item *stderr*)) list)
    (newline *stderr*)
    (exit 1)
)

(define (usage-exit)
    (die `("Usage: " ,*run-file* " filename"))
)

;takes input file (filename) and parses line by line
;if file nonexistent then errors out
;otherwise returns line from inputfile
(define (readlist-from-inputfile filename) 
    (let ((inputfile (open-input-file filename)))
         (if (not (input-port? inputfile))
             (die `(,*run-file* ": " ,filename ": open failed"))
             (let ((program (read inputfile)))
                  (close-input-port inputfile)
                         program))))

						 
(define (write-program-by-line filename program)
    (printf "==================================================~n")
    (printf "~a: ~s~n" *run-file* filename)
    (printf "==================================================~n")
    (printf "(~n")
    (map (lambda (line) (printf "~s~n" line)) program)
    (printf ")~n"))

(define (main arglist)
    (if (or (null? arglist) (not (null? (cdr arglist))))
        (usage-exit)
        (let* ((sbprogfile (car arglist))
               (program (readlist-from-inputfile sbprogfile)))
              (write-program-by-line sbprogfile program))))

(main (vector->list (current-command-line-arguments)))
