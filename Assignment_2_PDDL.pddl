;;Domain for cleaning floor tiles
;; A domain file for CMP2020M assignment 2018/2019

;; Define the name for this domain (needs to match the domain definition
;;   in the problem files)

(define (domain floor-tile)

	;; We only require some typing to make this plan faster. We can do without!
	(:requirements :typing)

	;; We have two types: robots and the tiles, both are objects
	(:types robot tile - object)

	;; define all the predicates as they are used in the probem files
	(:predicates  

    ;; described what tile a robot is at
    (robot-at ?r - robot ?x - tile)

    ;; indicates that tile ?x is above tile ?y
    (up ?x - tile ?y - tile)

    ;; indicates that tile ?x is below tile ?y
    (down ?x - tile ?y - tile)

    ;; indicates that tile ?x is right of tile ?y
    (right ?x - tile ?y - tile)

    ;; indicates that tile ?x is left of tile ?y
    (left ?x - tile ?y - tile)
    
    ;; indicates that a tile is clear (robot can move there)
    (clear ?x - tile)

    ;; indicates that a tile is cleaned
    (cleaned ?x - tile)
 	)




   ;;ACTIONS that need to be defined:

   ;;--------------------CLEANING THE TILES (Up,Down)-------------------------
   
   ;;This action makes the robot clean the tile above
   (:action clean-up
  
    ;;All of the actions have the same parameters. ?r = robot. ?y = current tile. ?x = target tile
    :parameters (?r - robot ?y - tile ?x - tile)
   
   ;;All of the actions have the same preconditions except the tile comparison changes based on the direction of the tiles.(eg up, down)
   ;;Check if the following conditions are TRUE: the robot is on the current tile, the target tile is
   ;;above the current tile and that the taget tile is clear so the robot can move there
    :precondition (and (robot-at ?r ?y) (up ?x ?y) (clear ?x))
   
   ;;Both of the cleaning actions have the same effects applied.
   ;;Set that the tile has been cleaned to TRUE and change that the tile is clear to FALSE so the robot can not move to that tile 
    :effect (and(cleaned ?x) (not(clear ?x)))
   )

   ;;This action makes the robot clean the tile below
   (:action clean-down
    :parameters (?r - robot ?y - tile ?x - tile)
    :precondition (and (robot-at ?r ?y) (down ?x ?y) (clear ?x))
    :effect (and(cleaned ?x) (not(clear ?x)))              
   )
   ;;-----------------MOVEMENT of the bot (Up,Down,Left,Right)------------------------
   
   ;;This action makes the robot move up the tile
   (:action up 
    :parameters (?r - robot ?y - tile ?x - tile)
    :precondition (and (robot-at ?r ?y) (up ?x ?y) (clear ?x) )
            
   ;;The movement actions have the same effects applied
   ;;Set the following conditions to TRUE: The robot is at the target tile and that starting tile is now clear
   ;;Set the following to FALSE: The robot is no longer at the starting tile and that the target tile is now not clear
    :effect (and(robot-at ?r ?x)(clear ?y)(not(robot-at ?r ?y))(not(clear ?x)))  
   )

   ;;This action makes the robot move down the tile
   (:action down 
    :parameters (?r - robot ?y - tile ?x - tile)
    :precondition (and (robot-at ?r ?y) (down ?x ?y) (clear ?x) )
    :effect (and(robot-at ?r ?x)(clear ?y)(not(robot-at ?r ?y))(not(clear ?x)))      
   )

   ;;This action makes the robot move to the right tile  
   (:action right 
    :parameters (?r - robot ?y - tile ?x - tile)
    :precondition (and (robot-at ?r ?y) (right ?x ?y) (clear ?x) )
    :effect (and(robot-at ?r ?x)(clear ?y)(not(robot-at ?r ?y))(not(clear ?x)))  
   )
    
   ;;This action makes the robot move  to the left tile
   (:action left 
    :parameters (?r - robot ?y - tile ?x - tile)
    :precondition (and (robot-at ?r ?y) (left ?x ?y) (clear ?x) )
    :effect (and(robot-at ?r ?x)(clear ?y)(not(robot-at ?r ?y))(not(clear ?x)))  
   )

)
;;References used:

;;Computer Science University of Toronto (undated) *An Introduction to PDDL*. 
;;Available from https://www.cs.toronto.edu/~sheila/2542/s14/A1/introtopddl2.pdf[accessed 24 May 2021]


;;Dr.Miao Yu(undated) *PLANNING*. University of Lincoln. 
;;Available from https://learn-eu-central-1-prod-fleet01-xythos.learn.cloudflare.blackboardcdn.com/5eec76bac93d5/3140963?X-Blackboard-Expiration=1622062800000&X-Blackboard-Signature=ipmhZb2bRNq2GIoLMn%2FapbNoIXizJU2wat0HtHzLd9U%3D&X-Blackboard-Client-Id=307403&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27CMP2020M%2520planning%25201.pdf&response-content-type=application%2Fpdf&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20210526T150000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=AKIAZH6WM4PL5M5HI5WH%2F20210526%2Feu-central-1%2Fs3%2Faws4_request&X-Amz-Signature=a3633fff27ce229d144f3faa25c427a09dde240a973f8ef981a7323f47b62b66
;;[accessed 24 May 2021]