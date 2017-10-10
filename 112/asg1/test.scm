(define (nutz poop) 
	(let ((p (open-input-file poop)))
  (let f ((x (read p)))
    (if (eof-object? x)
        (begin
          (close-input-port p)
          '())
        (display x))))
		)
		
(define *function-list* (make-hash))
		

	
