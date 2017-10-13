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
(define (label-got-key key)
		(hash-has-key? *label-table* key))
;retrieves from label table
(define (label-get key)
        (hash-ref *label-table* key))
;puts into label table
(define (label-put! key value)
        (hash-set! *label-table* key value))
		
;makes varriable table
(define *varriable-table* (make-hash))
;retrieves from varriable table
(define (varriable-got-key key)
		(hash-has-key? *varriable-table* key))
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
		(cond 
			((equal? relop '<>)not (= exp1 exp2))
			((equal? relop '<) (< exp1 exp2))
			((equal? relop '>) (> exp1 exp2))
			((equal? relop '<=)(<= exp1 exp2))
			((equal? relop '>=)(>= exp1 exp2))
			((equal? relop '=) (= exp1 exp2))))

;checks if statement
;if statment is true then returns label
(define (if-statement relop exp1 exp2 label)
	(if (comparison relop exp1 exp2)
		(label)
		#f))
			
;let function to define varriables in variable-table
;type true if array, false if symbol
(define (let-function varriable value)
	(if (null? (cadr varriable));checks if not array
		(variable-put varriable value)
		(if (varriable-got-key varriable);check to make sure is array
			(vector-set! (car varriable) (cadr varriable) value);set index to value
			(die '("non-vector returned in let-function")));error out if not array
		));puts varriable into symbol table
#|
(define (print-func accumulate shit)
		(cond 
		((string? shit)
			(append (accumulate)(shit)))
		((list? shit)
			(if (<= 2 (length shit))
				;print varriable 
				eval ))))
	|#	
	
(for-each
    (lambda (pair)
            (function-put! (car pair) (cadr pair)))
    `(
		(dim    ,(lambda (x y) (variable-put! x (make-vector y))));creates an array of y dimension
		(let    ,(lambda (var val) (let-function var val)));assigns varriables
		(goto   ,(lambda (x) (label-get x)));returns label data from label-table*
		(if     ,(lambda (relop exp1 exp2 label) (if-statement relop exp1 exp2 label)));if statement
		(print  ,(lambda (x) (display x)));print statement
		(input , (lambda (x) (x))) ;dont know how the fuck to do this left blank
        (log10_2 0.301029995663981195213738894724493026768189881)
        (sqrt_2  1.414213562373095048801688724209698078569671875)
        (e       2.718281828459045235360287471352662497757247093)
        (pi      3.141592653589793238462643383279502884197169399)
        (div     ,(lambda (x y) (floor (/ x y))))
        (log10   ,(lambda (x) (/ (log x) (log 10.0))))
        (mod     ,(lambda (x y) (- x (* (div x y) y))))
        (quot    ,(lambda (x y) (truncate (/ x y))))
        (rem     ,(lambda (x y) (- x (* (quot x y) y))))
        (+       ,(lambda (x y) (+ x y)))
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
    ;(exit 1)
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


;meat function						 
(define (go-around line)
		(if (null? line)
		'()
		(display (car line)))
		(printf "~n")
		(go-around (cdr line)))
		

(define (get-fucked line)
		;(if (pair? line)
		(display (car line)))		
		;(display "done"))
		;(get-fucked (cdr line)))
		
;evaluate function
;(define (test)
;	(let ([x "(print "Hello, World!")"])

(define (interpret_line shit)
	;(debug "butt")
	;(display shit)
	;(display (length shit))
	(cond 
		((= (length shit) 3) ;label and statement
		;(cons ((car shit) function_eval (cddr shit)))) ;get line # and statement
		(function_eval (caddr shit))
		(display "\n")) ;get line # and statement
		
		((= (length shit) 2); label or statement, either append label or statment
		;(cons ((car shit) (function_eval (cdr shit)))))
		(function_eval (cadr shit))
		(display "\n"))
		
		((= (length shit) 1); null line
		;(debug "asshile"))
		;(cons ((shit) '())))
		))
)

(define (debug x)
		(display x)
		(display "\n"))

(define (function_eval expr)
	;(debug "cock")
	;(display (list? expr))
	;(display (car expr))
	;(display (cadr expr))
	;(display (caddr expr))
	(cond
		((string? expr);if string
          ;(debug "string")
		  expr) 
		  ;(cons expr (function_eval (cdr expr))))
		  
		((number? expr);if number 
		  (debug "number")
		  expr)
		  ;(cons expr (function_eval (cdr expr))))
			
		((function-got-key expr) ;if key in func table
			(debug "function")
		  (function-get expr)) 
		  ;(cons (function-get expr) (function_eval (cdr expr))))
		  
		((list? expr) ;if list
		;(debug "list")
		(if (function-got-key (car expr)) ;the car is a function
			((debug "got function")
             (let((top (function-get (car expr))));let the top be the <func>
             	(cond
             	   ((procedure? top)
					;(map (lambda (line)  (printf "bit is ~s~n" (line))) (cdr expr))
					;(debug (cdr expr))
             	   	 (apply top (map (lambda (x) (debug x) (function_eval x)) (cdr expr))))
					 ;apply function-eval recursivly to rest of list
             	   ((vector? top)
             	   	(vector-ref top (cadr expr)))
             	   ((number? top)
             	   	top)
             	   (else
             	   	  (die "Fatal: Not in function table."))
                )
             )
			 )
			 ;otherwise it must be an error
             (die (list "Fatal error:"
             	         (car expr) " not in function table\n"))
		)
		)
     )
)	 

; Inserts all labels in program into label table
(define (scan-label program)
	(map (lambda (line) ;maps onto entire list that is program
		(when (not(null? line)) ;when theres actually something in line
		   (when (or (= (length line) 3) ;when theres 3 or 2 things
		   	         (and (= (length line) 2) ;if only 2 things make sure
		   	         	  (not (list? (cadr line))) ;its not a statement (list)
		   	         )
		   	     )
		          (label-put! (cadr line) (cddr line) );store label and statement of line
		   )
		  )
	      )
	program)
)


(define (write-program-by-line filename program)
    (printf "==================================================~n")
    (printf "~a: ~s~n" *run-file* filename)
    (printf "==================================================~n")
    (printf "(~n")
	;(display (car (cadr program)))	
	;program is already a list of lists
	;need to split list into components
	;(display (list? (car (car program))))
	;(display (string? (car program)))
	;(display "penis")
	;(map (lambda (line) (display line)) program)
	(scan-label program)
	;(display (label-get 'four))
	;(function_eval program)
	;(display "penis")
	;(map (lambda (line)  (printf "~s~n" (cadr line))) program)
    ;(map (lambda (line) (function_eval (cadr line))) program)
    (map (lambda (line) (interpret_line line)) program)
	
    (printf ")~n"))

(define (main arglist)
    (if (or (null? arglist) (not (null? (cdr arglist))))
        (usage-exit)
        (let* ((sbprogfile (car arglist))
               (program (readlist-from-inputfile sbprogfile)))
              (write-program-by-line sbprogfile program))))

;(main (vector->list (current-command-line-arguments)))
