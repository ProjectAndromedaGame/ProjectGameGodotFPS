extends Node

var mouse_capture : bool = false
@export var mouse_sens := 0.1            # ajusta a gusto
@export var pitch_min := -89.0
@export var pitch_max :=  89.0

enum ButtonFlags {
	NONE      = 0,
	IN_JUMP   = 1 << 0,
	IN_CROUCH = 1 << 1,
	IN_RUN    = 1 << 2,
	IN_SHOOT  = 1 << 3,
	IN_AIM    = 1 << 4,
	IN_RELOAD = 1 << 5,	
}

var seq: int = 0
var tick: int = 0
var dt: float = 0.0

var buttons: int = 0
var forward_move: float = 0.0
var side_move: float = 0.0
var up_move: float = 0.0
var view_delta: Vector2 = Vector2.ZERO
var view_angles: Vector2 = Vector2.ZERO
var user_cmd: Dictionary

func get_button_inputs() -> int:
	var temp := ButtonFlags.NONE
	if Input.is_action_pressed("action_jump"):          temp |= ButtonFlags.IN_JUMP;
	if Input.is_action_pressed("action_crouch"):        temp |= ButtonFlags.IN_CROUCH
	if Input.is_action_pressed("action_run"):           temp |= ButtonFlags.IN_RUN
	if Input.is_action_pressed("action_shoot"):         temp |= ButtonFlags.IN_SHOOT
	if Input.is_action_pressed("action_aim"):           temp |= ButtonFlags.IN_AIM
	if Input.is_action_pressed("action_reload"):   temp |= ButtonFlags.IN_RELOAD
	return temp

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseMotion:
		view_delta += event.relative

func _physics_process(_dt: float) -> void:
	seq  += 1
	tick += 1
	dt    = _dt

	buttons = get_button_inputs()
	# get_axis(NEGATIVE, POSITIVE)
	forward_move = Input.get_axis("action_backward", "action_forward")
	side_move    = Input.get_axis("action_left","action_right")
	up_move = Input.get_axis("action_crouch","action_jump")
	# up_move queda en 0.0 salvo que tengas vuelo/jetpack continuo
	# actualiza ángulos acumulados con el delta de este tick
	view_angles.x += view_delta.x * mouse_sens
	view_angles.y = clamp(view_angles.y - view_delta.y * mouse_sens, pitch_min, pitch_max) 
	
	user_cmd = build_usercmd()
	print(view_angles)
	Engine.get_singleton("GDBridge").set_user_cmd(user_cmd)
	

func build_usercmd() -> Dictionary:
	var cmd := {
		"seq": seq,
		"tick": tick,
		"dt": dt,
		"view_delta": view_delta,  
		"view_angles": view_angles,    # solo el delta de este tick
		"forward_move": forward_move,
		"side_move": side_move,
		"up_move": up_move,
		"buttons": buttons,
	}
	view_delta = Vector2.ZERO
	if view_angles.x > 360 or view_angles.x < -360:
		view_angles.x = 0# pitch (usa Y del mouse)
	
	return cmd # empieza capturado si quieres

func set_mouse_capture(on: bool) -> void:
	mouse_capture = on
	Input.set_mouse_mode( Input.MOUSE_MODE_CAPTURED if on else Input.MOUSE_MODE_VISIBLE )
	# evita “saltos” cuando recapturas
	if on:
		Input.warp_mouse(Vector2i(get_viewport().get_visible_rect().size / 2))
	# también puedes resetear deltas aquí si usas acumulación:
	# view_delta = Vector2.ZERO
		
func _input(event: InputEvent) -> void:
	if event.is_action_pressed("debug_mouse_toggle"):
		set_mouse_capture(!mouse_capture)
	if event.is_action_pressed("debug_exit"):
		if OS.has_feature("debug") or Engine.is_editor_hint():
			get_tree().quit()
		
func _ready() -> void:
	set_mouse_capture(true)
	
func test() -> String:
	return "this mesage is from godot, hello c++"
	
	
