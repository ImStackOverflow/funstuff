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
(define (function-got-key key)
		(hash-has-key? *function-table* key))
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
		#f))
			
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
		(input , (lambda (x) (x+1)))
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
