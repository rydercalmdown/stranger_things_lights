.PHONY: build
build:
	@docker-compose build

.PHONY: run
run:
	@docker-compose up

.PHONY: install-pi
install-pi:
	@cd scripts && bash install_raspberry_pi.sh

.PHONY: run-worker
run-worker:
	@. env/bin/activate && cd worker && python app.py

.PHONY: run-server
run-server:
	@docker-compose up -d web

.PHONY: push
push:
	@docker-compose push web

.PHONY: deploy
deploy:
	@kubectl apply -f deployment/redis -f deployment/web
