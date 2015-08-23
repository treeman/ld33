#include "engine/locator.hxx"
#include "monster.hxx"
#include "bullet.hxx"
#include "world.hxx"

Monster::Monster(World &world) : world(world) {
    spr = create_sprite("monster_main.png");

    // Basic one
    //bounds.add_rect(0, 0, 332, 305);

    // Real one
    bounds.add_rect(68, 74, 273, 250);
    bounds.add_rect(47, 248, 148, 287);
    bounds.add_rect(142, 250, 161, 275);
    bounds.add_rect(156, 256, 171, 269);
    bounds.add_rect(157, 248, 225, 258);
    bounds.add_rect(271, 142, 306, 223);
    bounds.add_rect(274, 224, 288, 241);
    bounds.add_rect(274, 224, 297, 232);
    bounds.add_rect(51, 76, 67, 248);
    bounds.add_rect(273, 123, 296, 144);
    bounds.add_rect(106, 6, 285, 77);
    bounds.add_rect(24, 118, 52, 156);
    bounds.add_rect(306, 164, 312, 200);
    bounds.add_rect(30, 156, 51, 172);
    bounds.add_rect(35, 172, 53, 189);

    monster_life = max_monster_life = 10000;
    is_dead = false;
}

void Monster::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::H) fire_left();
            if (e.key.code == sf::Keyboard::L) fire_right();
            break;
        default:
            break;
    }
}

void Monster::set_pos(FPoint _pos) {
    pos = _pos;
    // TODO better hitbox
    if (pos.x < 0) pos.x = 0;
    if (pos.x + width > 800) pos.x = 800 - width;
    if (pos.y < 0) pos.y = 0;
    if (pos.y + height > 500) pos.y = 500 - height;

    D_.tmp(fmt("monster pos: %f, %f", pos.x, pos.y));
    spr.setPosition(pos);
    bounds.set_pos(pos);
}

void Monster::move(FPoint dv) {
    set_pos(pos + dv);

    // Should only move this... T.T
    for (auto s : spawners) {
        s->move(dv);
    }
}

void Monster::update(const sf::Time &dt) {
    move_dir = IPoint();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move_dir.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move_dir.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move_dir.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move_dir.y += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) fire_eyes();

    FPoint dv = FPoint(move_dir).normalize() * move_speed * dt.asSeconds();
    move(dv);
}

void Monster::draw(sf::RenderWindow &w) {
    w.draw(spr);
    bounds.draw(w);
}

bool Monster::is_collision(shared_ptr<BaseBounds> b) {
    return bounds.intersects(b);
}

void Monster::fire_bullets(vector<Bullet*> bullets) {
    for (auto x = bullets.begin(); x != bullets.end(); ++x) {
        shared_ptr<Bullet> b(*x);
        world.add_bullet(b);
    }
}

void Monster::fire_eyes() {
    D_.tmp(fmt("pos: %f, %f", pos.x, pos.y));
    if (eyes_fire_delay.getElapsedTime().asSeconds() > 0.05) {
        string path = "cbullet.png";
        vector<Bullet*> bullets = {
            new VelBullet(path, 100, FPoint(1, 4), FPoint(115, 165) + pos, false),
            new VelBullet(path, 100, FPoint(1, 2), FPoint(185, 148) + pos, false),
        };
        fire_bullets(bullets);

        // Offset for monster position
        eyes_fire_delay.restart();
    }
}

void Monster::fire_left() {
    L_("IMBA PEW!\n");
    shared_ptr<Bulletspawner> spawner(new Bulletspawner(world));
    spawner->set_pos(FPoint(85, 240) + pos);
    const int num = 20;
    for (int i = 0; i < num; ++i) {
        spawner->add(i * 360 / num, 50, 0);
        spawner->add(i * 360 / num, 50, 0.5);
        spawner->add(i * 360 / num, 50, 1);
        spawner->add(i * 360 / num, 50, 1.5);
        spawner->add(i * 360 / num, 50, 2);
    }
    spawners.push_back(spawner);
    world.add_spawner(spawner);
}

void Monster::fire_right() {
    //const float r = 200;
    const float a = 50;
    const float b = .25;
    //const float th = deg2rad(30);
    const float av = deg2rad(200);

    string path = "cbullet.png";
    vector<Bullet*> bullets = {
        new FunBullet(path, 50, FPoint(292, 190) + pos,
            // theta = angle vel * time
            [a, b, av](float t) { return a * cos(av * t) * exp(b * av * t); },
            [a, b, av](float t) { return a * sin(av * t) * exp(b * av * t); },
            false)
    };
    fire_bullets(bullets);
}

void Monster::take_damage(float damage) {
    monster_life -= damage;
    if (monster_life < 0) {
        monster_life = 0;
        is_dead = true;
    }
}

